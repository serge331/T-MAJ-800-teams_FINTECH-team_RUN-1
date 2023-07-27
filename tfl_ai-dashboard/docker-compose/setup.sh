#!/usr/bin/env bash

CONTAINER_NAME=tfl_ai-app

cp -n .env.example .env

read -r -p "Enter the http port [8300]: " port
port=${port:-8300}

if [ -f .env.tmp ]; then
    rm .env.tmp
fi

sed '/DOCKER_WEB_PORT/d' .env > .env.tmp

echo "## DOCKER_WEB_PORT" >> .env.tmp
echo DOCKER_WEB_PORT="$port" >> .env.tmp

mv .env.tmp .env

docker-compose up -d

CONTAINER_ID=$(docker ps -aqf "name=$CONTAINER_NAME")

docker exec "$CONTAINER_ID" composer install
docker exec "$CONTAINER_ID" php artisan key:generate
docker exec "$CONTAINER_ID" php artisan migrate:fresh
docker exec "$CONTAINER_ID" php artisan db:seed
docker exec "$CONTAINER_ID" php artisan storage:link

# docker exec $CONTAINER_ID php artisan passport:install

echo ""
echo "All done, please visit http://localhost:$port"

echo ""
echo "If you want to run extra commands, it can be done like this: docker exec $CONTAINER_ID ls -l"

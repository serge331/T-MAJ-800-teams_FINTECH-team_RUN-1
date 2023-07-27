#!/usr/bin/env bash

CONTAINER_NAME=fctee-app
CONTAINER_ID=`docker ps -aqf "name=$CONTAINER_NAME"`

docker exec -it $CONTAINER_ID bash

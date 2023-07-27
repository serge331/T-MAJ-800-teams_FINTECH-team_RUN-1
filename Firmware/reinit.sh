#! /bin/sh

set -e

echo "Copying common library to each firmware"

cp -r ./Common_libraries/LoRaHandler ./Node/src/
cp -r ./Common_libraries/Protocol ./Node/src/

cp -r ./Common_libraries/LoRaHandler ./Gateway/src/
cp -r ./Common_libraries/Protocol ./Gateway/src/

echo "Sucessfully copied common library"
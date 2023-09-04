#!/bin/zsh

set -eu

CONTAINER_NAME=dev_nm
IMAGE_NAME=dev_nm_image

docker build -f Dockerfile . -t ${IMAGE_NAME} #--platform=linux/amd64 
docker build -f Dockerfile . --platform=linux/amd64 -t ${IMAGE_NAME}
docker run --detach --name ${CONTAINER_NAME} ${IMAGE_NAME}
docker run -it --mount type=bind,src="$(pwd)",target=/src --name devtest debian:latest bash

#!/bin/bash

set -eu

CONTAINER_NAME=dev_nm
IMAGE_NAME=dev_nm_image

if docker images | grep -q ${IMAGE_NAME}
then
	echo "Image already exist."
else
	docker build -f docker/Dockerfile . --platform=linux/amd64 -t ${IMAGE_NAME}
fi

if docker ps -a | grep -q ${CONTAINER_NAME}
then
	echo "Container already exist. Running it..."
	docker start -i ${CONTAINER_NAME}
else
	docker run -it --mount type=bind,src="$(pwd)",target=/src --name ${CONTAINER_NAME} ${IMAGE_NAME}
fi

#### Installation

```bash
$ sudo apt-get install docker docker-compose docker.io
```

---

#### Docker Images

```bash
# download an image from docker-hub
$ docker pull <image_name>

# list all images on the system
$ docker image ls -a

# remove an image (first 4 characters of image id will also work)
$ docker image rm e445ab08b2be
```

---

#### Containers

```bash
# creating a new container
$ docker run -it --publish 80:80 <image_name>

# list all containers 
$ docker container ls -a

# remove container (first 4 characters of the container id will also work)
$ docker container rm 608e8e728321 

# delete all containers
$ docker container rm $(docker ps -a -q) -f
```

---

#### Environment variables

```bash
# containers can be started with specific env variables
$ docker container run -p 8080:5432 --env POSTGRES_PASSWORD=mypassword --name postgres postgres


# an env file can also be passed, containing multiple env variables
$ docker run --env-file ./env ubuntu bash
```

---

#### Volumes

Folders from outside the container (i.e. host) can be mapped on to specific folders inside the container. This way our container can use a folder from outside its operating environment i.e. client machine. E.g. We can map the current directory to the default site folder for `nginx`.

```bash
$ docker container run -p 80:80 -v $(pwd):/usr/share/nginx/html nginx
```


---

#### Entering running container

```bash
# drop to container shell
$ docker container exec -it <container-name> sh
```


---

#### Launch and enter a temporary container

```bas
$ docker run -i -t --rm alpine:latest sh
```


---

#### Docker and Node

```bash
# running node inside docker container
$ docker run --rm -it --tty -v $(pwd):/app -w /app node:20-alpine node main.mjs

# running NPM inside docker container 
$ docker run --rm -it --tty -v $(pwd):/app -w /app node:20-alpine npm install
```

- `--rm` flag will remove the container after the script is done executing
- `-w` fag sets the current working directory (inside container) for the command


---

#### Docker and PHP

```bash
# running PHP inside docker container
$ docker run --rm -p 8000:8000 -v $(pwd):/app -w /app php:7.4 php -S 0.0.0.0:8000
```

- We have mapped port `8000` from container to port `8000` of the host OS
- Server will serve files inside the `pwd` on `localhost:8000` of the host OS

```bash
# running composer inside docker container 
$ docker run --rm -it --tty -v $(pwd):/app -w /app composer:latest composer --ignore-platform-reqs install
```

- Composer image will use the latest version of PHP when running composer. This is not a problem because we are only managing packages using composer 
- `ignore-platform-requirements` means that we ignore the PHP version specified in the `composer.json` file.


---

#### Docker and Python

```bash
# pull docker image
$ docker pull python:3.11-alpine

# start the temporary image
$ docker run --rm -it -v $(pwd):/app -w /app --tty python:<version> sh
```

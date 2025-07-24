
```.dockerignore
.git
node_modules
build
dist
.env
```

```Dockerfile
FROM node:24-alpine

# set current pwd.
WORKDIR /app

# only copy package.json and package-lock.json. This means that this step will
# only run in case these two files change i.e. project dependencies have 
# changed.
COPY package*.json ./

RUN npm install
COPY . .
RUN npm run build

EXPOSE 3000
CMD ["npm", "start"]
```

```bash
$ docker build -t my-node-app /path/to/source
```


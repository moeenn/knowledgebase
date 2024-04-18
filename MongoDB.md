- JSON schema [Link](https://www.mongodb.com/docs/manual/core/schema-validation/specify-json-schema/) [Link](https://www.mongodb.com/basics/json-schema-examples)
- NodeJS driver [Link](https://www.npmjs.com/package/mongodb)


#### Run using Docker

```yml
version: '3.8'
services:
  mongodb:
    image: mongo:7.0-jammy
    ports:
      - '27017:27017'
    environment:
      - MONGO_INITDB_ROOT_USERNAME=devuser
      - MONGO_INITDB_ROOT_PASSWORD=devpass
      - MONGO_INITDB_DATABASE=dev
    volumes:
      - ./docker-volume:/data/db
```


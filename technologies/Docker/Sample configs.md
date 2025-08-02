
#### PostgreSQL

```yml
services:
  db:
    container_name: "postgres-db"
    image: postgres:15.3-alpine
    restart: always
    environment:
      - POSTGRES_USER=devuser
      - POSTGRES_PASSWORD=devpass
      - POSTGRES_DB=dev
    volumes:
      - ./docker-volume:/var/lib/postgresql/data
    ports:
      - "5432:5432"
```

**Note**: The connection string will be as follows.

```
postgresql://user:pass@localhost:5432/dev?sslmode=disable
```


---

#### MongoDB

```yml
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


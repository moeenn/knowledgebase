
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
    image: mongodb/mongodb-community-server:6.0-ubi8
    environment:
      - MONGODB_INITDB_ROOT_USERNAME=devuser
      - MONGODB_INITDB_ROOT_PASSWORD=devpass
      - MONGODB_INITDB_DATABASE=dev
    volumes:
      - mongodb_data:/data/db

volumes:
  mongodb_data:
    driver: local
```


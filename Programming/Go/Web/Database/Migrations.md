#### Running migrations

```bash
# install golang-migrate
$ go install -tags 'postgres' github.com/golang-migrate/migrate/v4/cmd/migrate@latest
```

```bash
export MIGRATIONS_PATH = migrations
export DB_CONNECTION = postgresql://user:pass@localhost:5432/dev?sslmode=disable

# create new migration file
$ migrate create -ext sql -dir ${MIGRATIONS_PATH} -seq migration_name

# run all pending migrations
$ migrate -path '${MIGRATIONS_PATH}' -database ${DB_CONNECTION} -verbose up

# clear database and drop all tables
$ migrate -database ${DB_CONNECTION} drop
```

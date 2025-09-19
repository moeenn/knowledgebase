#### Running migrations

```bash
# install golang-migrate
$ go install -tags 'postgres' github.com/golang-migrate/migrate/v4/cmd/migrate@latest
```


#### Taskfile example

```yml
version: '3'

dotenv: ['.env']

vars:
  MIGRATIONS_PATH: ./migrations

tasks:
  # usage: NAME=create_sample_table task migrate:create
  "migrate:create":
    cmds:
      - migrate create -ext sql -dir {{.MIGRATIONS_PATH}} -seq $NAME

  "migrate:up":
    cmds:
      - migrate -path '{{.MIGRATIONS_PATH}}' -database $DB_CONNECTION -verbose up

  "migrate:drop":
    cmds:
      - migrate -path {{.MIGRATIONS_PATH}} -database $DB_CONNECTION drop
```

```.env
DB_CONNECTION=postgresql://user:pass@localhost:5432/dev?sslmode=disable
```

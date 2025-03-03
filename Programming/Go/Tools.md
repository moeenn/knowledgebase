We can use the following shell script to install all tools required for the project.

```sh
#! /bin/bash

declare -a tools=(
  "github.com/go-task/task/v3/cmd/task@latest"
  "github.com/joho/godotenv/cmd/godotenv@latest"
  "github.com/nametake/golangci-lint-langserver@latest"
  "github.com/golangci/golangci-lint/cmd/golangci-lint@latest"
  "github.com/golang-migrate/migrate/v4/cmd/migrate@latest"
  "github.com/sqlc-dev/sqlc/cmd/sqlc@latest"
)

for tool in ${tools[@]}; do
  eval "go install -v ${tools}"
done
```
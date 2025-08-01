
#### Installation

```bash
$ go install github.com/go-task/task/v3/cmd/task@latest
```


#### Basic usage
Create a file named `Taskfile.yml` at the root of the project and add the following content.

```yml
version: '3'

tasks:
  run:
    cmds:
	  - task: test
      - go run .

  test:
	cmds:
      - go test -v ./...
```


#### Variables

```yml
version: '3'

vars:
  MIGRATIONS_PATH: ./db/migrations

tasks:
  "migrate:drop":
    cmds:
      - migrate -path {{.MIGRATIONS_PATH}} drop
```


#### Loading environment files

```yml
version: '3'

dotenv: ['.env']

tasks:
  migrate:
    - migrate -database $DB_CONNECTION up
```

**Note**: In this example we are using the variable `DB_CONNECTION` defined inside the `.env` file.


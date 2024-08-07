
```bash
$ sudo apt-get install golang

# install language server manually
$ go install golang.org/x/tools/gopls@latest
$ go install github.com/nametake/golangci-lint-langserver@latest
$ go install github.com/go-delve/delve/cmd/dlv@latest

# linting tools
$ go install honnef.co/go/tools/cmd/staticcheck@latest
$ go install github.com/kisielk/errcheck@latest

# optional linters
$ go install github.com/jgautheron/goconst/cmd/goconst@latest

# running linters 
$ staticcheck ./... && errcheck ./... 
$ goconst ./...
```

##### Modules
It is no longer compulsory to place your project files inside the directories specified above. Current versions of Go have introduced Go Modules. Inside any normal folder in the system, we can execute the following command to create a Go Module.

```bash
$ go mod init <program_name>
```


##### Install Project Dependencies
When we run a project, Go detects all dependencies of the project. We can install all project dependencies using the following command. The following also looks for any unused dependencies and removes them.

```bash
$ go mod tidy
```


##### Live reload 
```bash
# live reload on code changes
$ go install github.com/air-verse/air@latest
```
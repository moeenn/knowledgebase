
```bash
# install common tools
$ go install golang.org/x/tools/gopls@latest
$ go install github.com/go-delve/delve/cmd/dlv@latest
$ go install github.com/nametake/golangci-lint-langserver@latest
$ go install github.com/golangci/golangci-lint/cmd/golangci-lint@latest
```

---

#### Modules

It is no longer compulsory to place your project files inside the directories specified above. Current versions of Go have introduced Go Modules. Inside any normal folder in the system, we can execute the following command to create a Go Module.

```bash
$ go mod init <program_name>
```


---

##### Configuring linters

Create a `.golangci.yml` file at the root of the project. Sample content are as follows.

```yml
linters:
  enable:
    - exhaustive
    - exhaustruct
    - gosec
    - nilnil
    - nilerr
    - contextcheck
    - err113
    - gochecknoinits
    - godox
    - misspell

issues:
  exclude-dirs:
    - some/generated/code
```

**Note**: Run the following command to get a list of all supported linters.

```bash
# list available linters
$ golangci-lint linters

# run linters
$ golangci-lint run ./...
```


---

#### Install Project Dependencies

When we run a project, Go detects all dependencies of the project. We can install all project dependencies using the following command. The following also looks for any unused dependencies and removes them.

```bash
$ go mod tidy
```

##### Installing dependencies from private sources

```bash
$ export GOPRIVATE=github.com/<repo-name>
$ go get github.com/<repo-name>
```

**Note**: Ensure that `git` is configured and can access the private repo. Also add the following inside you `.gitconfig` file.

```yml
# use ssh instead of https for cloning
[url "ssh://git@github.com/"]
    insteadOf = https://github.com/
```


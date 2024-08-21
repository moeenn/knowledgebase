#### Simple example

```go
package main

import (
  "encoding/json"
  "log/slog"
  "net/http"
  "os"
)

const (
  ADDRESS = "0.0.0.0:5000"
)

func main() {
  logger := slog.New(slog.NewJSONHandler(os.Stdout, nil))
  mux := http.NewServeMux()

  userController := UserController{Logger: logger}
  userController.RegisterRoutes(mux)

  logger.Info("starting web server", "address", ADDRESS)
  if err := http.ListenAndServe(ADDRESS, mux); err != nil {
    logger.Error("failed to start web server", "error", err.Error())
    os.Exit(1)
  }
}

type UserController struct {
  Logger *slog.Logger
}

func (c *UserController) RegisterRoutes(mux *http.ServeMux) {
  mux.HandleFunc("GET /api/v1/users", c.ListAllUsers())
}

type User struct {
  Id       int    `json:"id"`
  Email    string `json:"email"`
  IsActive bool   `json:"is_active"`
}

type ListAllUsersResponse struct {
  Users []User `json:"users"`
}

func (c *UserController) ListAllUsers() http.HandlerFunc {
  return func(w http.ResponseWriter, r *http.Request) {
    c.Logger.Info("listing all users")

    res := ListAllUsersResponse{
      Users: []User{
        {Id: 10, Email: "admin@site.com", IsActive: true},
        {Id: 20, Email: "user@site.com", IsActive: false},
      },
    }

    w.WriteHeader(http.StatusOK)
    if err := json.NewEncoder(w).Encode(res); err != nil {
      c.Logger.Warn("failed to convert response into json", "error", err.Error())
    }
  }
}

```


---

#### Common HTTP types

##### `http.HandlerFunc`

This is the type of function which is responsible for processing the incoming HTTP request. It is defined as follows.

```go
type HandlerFunc func(ResponseWriter, *Request)
```

An example of this type is as follows.

```go
func GreetHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	json.NewEncoder(w).Encode(GreetResponse{
		Type: "greeting",
		Name: "sample",
	})
}
```


##### `http.Handler`

This is an interface which is implemented by all routers which can be passed to `http.ListenAndServe`. It is defined as follows.

```go
type Handler interface {
	ServeHTTP(ResponseWriter, *Request)
}
```

We can implement our own router by satisfying this interface.

```go
func main() {
	router := &CustomRouter{}
	http.ListenAndServe("0.0.0.0:3000", router)
}

// implements: http.Handler
type CustomRouter struct{}

func (router *CustomRouter) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodGet && r.URL.Path == "/" {
		GreetHandler(w, r)
	}
}
```


##### `mux.HandlerFunc`

This is a method on the `http.ServeMux` which allows us to register `http.HandlerFunc` functions. It can be used as follows.

```go
mux := http.NewServeMux()
mux.HandleFunc("GET /{name}", GreetHandler)
http.ListenAndServe("0.0.0.0:3000", mux)
```


---

#### Serving static files

```go
// files will be accessed from: <server>/public/*
fs := http.FileServer(http.Dir("./public"))
mux.Handle("/public/", http.StripPrefix("/public", fs))
```


---



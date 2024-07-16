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


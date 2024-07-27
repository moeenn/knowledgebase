#### Simple example

```go
package main

import (
	"log"
	"net/http"
	"sandbox/handlers"
)

const (
	ADDRESS = "0.0.0.0:3000"
)

func main() {
	mux := http.NewServeMux()

	// register all route handler here
	mux.HandleFunc("/", handlers.HomeHandler)

	// serve static files: access at <server>/public/*
	fs := http.FileServer(http.Dir("./public"))
	mux.Handle("/public/", http.StripPrefix("/public", fs))

	// start the server process
	log.Printf("starting server on %s\n", ADDRESS)
	http.ListenAndServe(ADDRESS, mux)
}
```

```go
package handlers

import (
	"encoding/json"
	"net/http"
)

type HomeResponse struct {
	Message string `json:"message"`
}

func HomeHandler(w http.ResponseWriter, r *http.Request) {
	res := HomeResponse{
		Message: "Hello world",
	}

	json.NewEncoder(w).Encode(res)
}
```

*Note*: Go has also introduced structured logging in version `1.20`. It appears to a better alternative to `log` package. Please use that instead.


#### Managing templates

```go
package templates

import (
	"html/template"
	"io"
	"sandbox/pkg/user"
)

var tmpl *template.Template

/* templates will be parsed once at package first import */
func init() {
	if tmpl == nil {
		var err error
		tmpl, err = template.ParseGlob("./pkg/templates/views/**/*.html")
		if err != nil {
			panic("failed to load template: " + err.Error())
		}
	}
}

type UserTableRows struct {
	Users []user.User
}

/* all pages and partials will have their own typed functions for execution */
func UserRowPartialTemplate(w io.Writer, user user.User) {
	tmpl.ExecuteTemplate(w, "user_row.partial.html", user)
}

func UserTableRowsPartialTemplate(w io.Writer, users []user.User) {
	tmpl.ExecuteTemplate(w, "user_table_rows.partial.html", UserTableRows{
		Users: users,
	})
}

func HomePageTemplate(w io.Writer, users []user.User) {
	tmpl.ExecuteTemplate(w, "home.page.html", UserTableRows{
		Users: users,
	})
}
```
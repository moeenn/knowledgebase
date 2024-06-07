```
main.go
go.mod
public/
	css/
		styles.css
	img/
		favicon.ico
pkg/
	controllers/
		controllers.go
	templates/
		templates.go
		views/
			layouts/
				base.layout.html
			pages/
				about.page.html
				home.page.html
				error.page.html
			partials/
				navbar.partial.html
```

```go
package main

import (
	"log"
	"net/http"
	"sandbox/pkg/controllers"
)

const (
	ADDRESS = "0.0.0.0:3000"
)

func main() {
	mux := http.NewServeMux()

	/* register all route handler here */
	mux.HandleFunc("/about", controllers.AboutHandler)
	mux.HandleFunc("/", controllers.HomeHandler)

	/* serve static files */
	fs := http.FileServer(http.Dir("./public"))
	mux.Handle("/public/", http.StripPrefix("/public", fs))

	/* start the server process */
	log.Printf("starting server on %s\n", ADDRESS)
	http.ListenAndServe(ADDRESS, mux)
}
```

```go
package controllers

import (
	"net/http"
	"sandbox/pkg/templates"
)

func HomeHandler(w http.ResponseWriter, r *http.Request) {
	/* Note: all 404s are redirected to '/' handler */
	if r.URL.Path != "/" {
		templates.ErrorPageTemplate(w, templates.ErrorPageArgs{
			Status:  http.StatusNotFound,
			Message: "Not found",
		})
		return
	}

	templates.HomePageTemplate(w)
}

func AboutHandler(w http.ResponseWriter, r *http.Request) {
	templates.AboutPageTemplate(w)
}
```

```go
package templates

import (
	"fmt"
	"html/template"
	"io"
)

var tmpl *template.Template

/* templates will be parsed once at package first import */
func init() {
	if tmpl == nil {
		tmpl = template.Must(template.ParseGlob("./pkg/templates/views/**/*.html"))
	}
}

func HomePageTemplate(w io.Writer) {
	if err := tmpl.ExecuteTemplate(w, "home.page.html", nil); err != nil {
		fmt.Println(err)
	}
}

func AboutPageTemplate(w io.Writer) {
	if err := tmpl.ExecuteTemplate(w, "about.page.html", nil); err != nil {
		fmt.Println(err)
	}
}

type ErrorPageArgs struct {
	Status  int
	Message string
}

func ErrorPageTemplate(w io.Writer, args ErrorPageArgs) {
	if err := tmpl.ExecuteTemplate(w, "error.page.html", args); err != nil {
		fmt.Println(err)
	}
}
```

```css
* {
  font-weight: normal;
}

body {
  font-family: Arial, Helvetica, sans-serif;
  padding: 1rem;
}

:is(p, span, a) {
  font-size: 0.9rem;
  line-height: 1.4rem;
}

nav {
  border-bottom: 1px dashed hsl(0, 0%, 70%);
}

nav, .nav-links {
  display: flex;
}

nav .nav-links {
  margin-left: auto;
}

nav a {
  padding: 0.5rem 1.1rem;
  text-decoration: none;
  margin: auto 0;
}

.page-error {
  padding: 5rem 0;
  display: flex;
}

.page-error p {
  margin: 0 auto;
  font-size: 1.2rem;
}
```

```html
{{ define "base.layout.start" }}
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <link rel="stylesheet" href="/public/css/styles.css" />
  <link rel="icon" type="image/x-icon" href="/public/img/favicon.ico" />
  <title>My website - {{ template "title" . }}</title>
</head>

<body>
  <aside>
    {{ template "navbar.partial" . }}
  </aside>
  <section>
    <main>
{{ end }}

{{ define "base.layout.end" }}
    </main>
  </section>
</body>
</html>
{{ end }}
```

```html
{{ define "navbar.partial" }}
<nav>
  <h3>Logo</h3>
  <div class="nav-links">
    <a href="/">Home</a>
    <a href="/about">About</a>
  </div>
</nav>
{{ end }}
```

```html
{{ define "title" }}Home{{ end }}
{{ template "base.layout.start" . }}
<div>
  <h1>Welcome to the home page</h1>
  <p>Lorem ipsum, dolor sit amet consectetur elit. Vero saepe harum nulla in adipisci ex doloribus cupiditate hic
    perferendis ab dolorem molestiae minima, ipsa unde qui eveniet. Facilis, dolores!
  </p>

  <button>Click me</button>
</div>
{{ template "base.layout.end" . }}
```

```html
{{ define "title" }}About{{ end }}
{{ template "base.layout.start" . }}
<div>
  <h1>About page</h1>
  <p>Lorem ipsum, dolor sit amet consectetur elit. Vero saepe harum nulla in adipisci ex doloribus cupiditate hic
    perferendis ab dolorem molestiae minima, ipsa unde qui eveniet. Facilis, dolores!
  </p>
</div>
{{ template "base.layout.end" . }}
```

```html
{{ define "title" }}Error{{ end }}
{{ template "base.layout.start" . }}
<div class="page-error">
  <p>{{ .Status }} - {{ .Message }}</p>
</div>
{{ template "base.layout.end" . }}
```


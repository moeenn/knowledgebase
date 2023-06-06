```
go.mod
main.go
views/
  base.layout.html
  home.page.html
```

```html
<!-- base.layout.html -->
{{ define "base.layout" }}
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="https://cdn.simplecss.org/simple.min.css">
  <title>{{ template "title" . }}</title>
</head>

<body>
  <section>
    <main>
      {{ template "content" . }}
    </main>
  </section>
</body>

</html>
{{ end }}
```

```html
<!-- home.page.html -->
{{template "base.layout" . }}

{{ define "title" }}Awesome Website{{ end }}
{{ define "content" }}
<div>
  <h1>Welcome to the home page</h1>
  <p>Lorem ipsum, dolor sit amet consectetur elit. Vero saepe harum nulla in adipisci ex doloribus cupiditate hic perferendis ab dolorem molestiae minima, ipsa unde qui eveniet. Facilis, dolores!
  </p>

  <button>Click me</button>
</div>
{{ end }}
```

```go
/* main.go */
package main

import (
  "fmt"
  "html/template"
  "os"
)

func main() {
  templates, err := template.ParseGlob("views/*.html")
  if err != nil {
    fmt.Println("error: failed to parse template files")
    os.Exit(1)
  }

  /* os.Stdout also implements io.Writer interface */
  templates.ExecuteTemplate(os.Stdout, "home.page.html", nil)
}
```

```go
/* main.go */
package main

import (
  "fmt"
  "html/template"
  "os"
)

/**
 * interface for io.Writer
 *
 * type Writer interface {
 *   Write(p []byte) (n int, err error)
 * }
 *
 */
type Writer struct{}

func (w Writer) Write(p []byte) (n int, err error) {
  n = 0
  err = nil

  fmt.Printf("%s", p)
  return n, err
}

func main() {
  templates, err := template.ParseGlob("views/*.html")
  if err != nil {
    fmt.Println("error: failed to parse template files")
    os.Exit(1)
  }

  writer := Writer{}

  templates.ExecuteTemplate(writer, "home.page.html", nil)
}
```

The above code will print the output to the console. The following code will spin up a web server and server the compiled template HTML

```go
/* main.go */
package main

import (
  "fmt"
  "html/template"
  "net/http"
  "os"
)

func main() {
  templates, err := template.ParseGlob("views/*.html")
  if err != nil {
    fmt.Println("error: failed to parse template files")
    os.Exit(1)
  }

  http.HandleFunc("/", Router(templates))
  http.ListenAndServe(":3000", nil)
}

func Router(templates *template.Template) http.HandlerFunc {
  return func(w http.ResponseWriter, r *http.Request) {
    templates.ExecuteTemplate(w, "home.page.html", nil)
  }
}
```


---

#### Serving static resources
Compiled HTML will include static resources like images, fonts etc. We can set up our server to serve this content from folder named `assets` in the root of the project.

```go
/* main.go */
func main() {
  ...
  fs := http.FileServer(http.Dir("assets/"))
  http.Handle("/public/", http.StripPrefix("/public/", fs))
  ...
}
```

Inside our templates, we can access our assets as follows.

```html
<div>
  <img src="/public/image.jpg" alt="image" />
</div>
```


---

#### Dynamic data in templates
```go
/* todos.go */
package main

type Todo struct {
  Title string
  Done  bool
}

var Todos []Todo = []Todo{
  {Title: "Task item one", Done: false},
  {Title: "Second item in list", Done: true},
  {Title: "A third item", Done: false},
}
```

```go
/* main.go */
...
func Router(templates *template.Template) http.HandlerFunc {
  return func(w http.ResponseWriter, r *http.Request) {
    templates.ExecuteTemplate(w, "home.page.html", Todos)
  }
}
```

```html
<!-- home.page.html -->
{{template "base.layout" . }}

{{ define "title" }}Awesome Website{{ end }}
{{ define "content" }}
<div>
  <table>
    <tbody>
      {{ range . }}
      <tr>
        <td>
          <input type="checkbox" {{ if .Done }} checked="checked" {{ end }}>
        </td>
        <td>{{ .Title }}</td>
      </tr>
      {{ end }}
    </tbody>
  </table>
</div>
{{ end }}
```


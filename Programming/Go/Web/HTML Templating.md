
##### File structure 

```
main.go
views
	pages/
		users.page.html
	layouts/
		base.layout.html
	partials/
		users_table.partial.html
```

```go
import (
  "html/template"
)

func main() {
  templates, err := template.ParseGlob("views/**/*.html")
  if err != nil {
    logger.Error("failed to load html templates", "error", err.Error())
    os.Exit(1)
  }
}
```

**Note**: The type for variable `templates` is `*template.Template`.

```go
type User struct {
  Id       int    `json:"id"`
  Email    string `json:"email"`
  IsActive bool   `json:"is_active"`
}

func (c *UserController) ListAllUsersPage() http.HandlerFunc {
  return func(w http.ResponseWriter, r *http.Request) {
    res := ListAllUsersResponse{
      Users: c.UserRepository.ListAllUsers(),
    }

    if err := c.Templates.ExecuteTemplate(w, "users.page.html", res); err != nil {
      c.Logger.Error("failed to execute template with data", "error", err.Error())
    }
  }
}

```

**Note**
- `ExecuteTemplate` is a method on type `*template.Template`.
- `users.page.html` is the exact name of the template file being rendered.

```html
{{ define "base.layout.start" }}
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css" />
  {{ template "header" . }}
</head>

<body class="container">
  {{ end }}

  {{ define "base.layout.end" }}
</body>

</html>
{{ end }}
```

```html
{{ define "header" }}
  <title>Sandbox - Users</title>
{{end }}

{{ template "base.layout.start" . }}
  {{ template "users_table.partial" . }}
{{ template "base.layout.end" . }}
```

```html
{{ define "users_table.partial" }}
<table>
  <thead>
    <tr>
      <th>Id</th>
      <th>Email</th>
      <th>Status</th>
    </tr>
  </thead>

  <tbody>
    {{ range .Users }}
    <tr>
      <td>{{ .Id }} </td>
      <td>{{ .Email }}</td>
      <td>{{ if .IsActive }}Active{{ else }}Inactive{{end}}</td>
    </tr>
    {{ end }}
  </tbody>
</table>
{{ end }}
```
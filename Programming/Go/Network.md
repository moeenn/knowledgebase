
#### Making network requests

```go
package main

import (
  "encoding/json"
  "fmt"
  "io"
  "net/http"
  "os"
)

type Todo struct {
  UserId    int    `json:"userId"`
  Id        int    `json:"id"`
  Title     string `json:"title"`
  Completed bool   `json:"completed"`
}

func FetchTodo(id int) (*Todo, error) {
  url := fmt.Sprintf("https://jsonplaceholder.typicode.com/todos/%d", id)
  todo := &Todo{}

  req, err := http.NewRequest(http.MethodGet, url, nil)
  if err != nil {
    return todo, err
  }
  req.Header.Add("Content-Type", "application/json")

  res, err := http.DefaultClient.Do(req)
  if err != nil {
    return todo, err
  }
  // fmt.Printf("Status: %d\n", res.StatusCode)

  body, err := io.ReadAll(res.Body)
  if err != nil {
    return todo, err
  }

  if err = json.Unmarshal(body, todo); err != nil {
    return todo, err
  }

  return todo, nil
}

func main() {
  todo, err := FetchTodo(1)
  if err != nil {
    fmt.Fprintf(os.Stderr, "error: %s\n", err.Error())
    os.Exit(1)
  }

  fmt.Printf("todo: %+v\n", todo)
}
```
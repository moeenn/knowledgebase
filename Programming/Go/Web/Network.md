
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

  // Note: DefaultClient does not timeout automatically 
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


#### Timeout request

```go
client := http.Client{
  Timeout: time.Second * 5,
}

res, err := client.Get(url)
```


#### Making request with body

```go
package main

import (
  "bytes"
  "encoding/json"
  "fmt"
  "io"
  "net/http"
  "os"
)

type User struct {
  Name  string `json:"name"`
  Email string `json:"email"`
}

func CreateUser(user *User) (*User, error) {
  url := "https://postman-echo.com/post"
  resultUser := &User{}

  encoded, err := json.Marshal(user)
  if err != nil {
    return resultUser, err
  }

  body := bytes.NewReader(encoded)
  req, err := http.NewRequest(http.MethodPost, url, body)
  if err != nil {
    return resultUser, err
  }

  res, err := io.ReadAll(req.Body)
  if err != nil {
    return resultUser, err
  }

  if err := json.Unmarshal(res, resultUser); err != nil {
    return resultUser, err
  }

  return resultUser, nil
}

func main() {
  user := User{
    Name:  "Admin",
    Email: "admin@@site.com",
  }

  resultUser, err := CreateUser(&user)
  if err != nil {
    fmt.Fprintf(os.Stderr, "error: %s\n", err.Error())
    os.Exit(1)
  }

  fmt.Println(resultUser)
}
```
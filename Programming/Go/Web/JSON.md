```go
package main

import (
  "encoding/json"
  "fmt"
)

type User struct {
  Id    uint   `json:"id"`
  Name  string `json:"name"`
  Email string `json:"email"`
  Age   uint   `json:"age,omitempty"`
}

func main() {
  user := User{
    Id:    30,
    Name:  "Sample",
    Email: "sample@site.com",
    Age:   21,
  }

  // encodedBytes is a byte slice i.e. []byte
  encodedBytes, err := json.Marshal(user)
  if err != nil {
    fmt.Printf("error: %v\n", err)
    return
  }

  fmt.Printf("encoded: %s\n", encodedBytes)
}
```

**Note**: Any private strict field will not be included in the encoded JSON.


##### Hide fields in Marshalled JSON
In the following example, `Password` field will not be included in the marshaled JSON.

```go
type User struct {
  Id       uint
  Name     string
  Email    string
  Password string `json:"-"`
  Profile  Profile
}
```


---

#### Unmarshal JSON

```go
func main() {
  jsonString := `{"id":30,"name":"Sample","email":"sample@site.com","age":21}`
  bytes := []byte(jsonString)

  var user User
  if err := json.Unmarshal(bytes, &user); err != nil {
    fmt.Printf("error: %v\n", err)
    return
  }

  fmt.Printf("%+v\n", user)
}
```


---

#### Check validity of JSON string

```go
package main

import (
	"encoding/json"
	"fmt"
)

func main() {
	raw := []byte("{ \"message\": \"hello world\"}")
	isValid := json.Valid(raw)

	fmt.Printf("%v\n", isValid)
}
```


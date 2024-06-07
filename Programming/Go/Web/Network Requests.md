
#### Simple GET Request 

```go
package main

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
)

type Post struct {
	Id     int    `json:"id"`
	UserId int    `json:"userId"`
	Title  string `json:"title"`
	Body   string `json:"body"`
}

func (p Post) String() string {
	return fmt.Sprintf("Post(id=%d, userId=%d, title='%s')", p.Id, p.UserId, p.Title)
}

func GetPostById(id int) (Post, error) {
	url := fmt.Sprintf("%s/%d", "https://jsonplaceholder.typicode.com/posts", id)
	res, err := http.Get(url)
	if err != nil {
		return Post{}, err
	}

	var body []byte
	if body, err = io.ReadAll(res.Body); err != nil {
		return Post{}, err
	}

	var post Post
	if err := json.Unmarshal(body, &post); err != nil {
		return Post{}, err
	}

	return post, nil
}

func main() {
	post, err := GetPostById(1)
	if err != nil {
		log.Fatalf("error: %s\n", err.Error())
		return
	}

	fmt.Printf("%s\n", post.String())
}
```


#### POST Request

```go
package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
)

type User struct {
	Name  string `json:"name"`
	Email string `json:"email"`
}

/**
 * the response has more fields, but these are the ones we care about
 * they can be safely ignored
 */
type PostResponse struct {
	Data User `json:"data"`
}

func main() {
	user := User{
		Name:  "Mr. Example",
		Email: "example@site.com",
	}

	marshalled, err := json.Marshal(user)
	if err != nil {
		log.Fatalf("error: %s\n", err.Error())
		return
	}

	requestBody := bytes.NewBuffer(marshalled)

	url := "https://postman-echo.com/post"
	res, err := http.Post(url, "application/json", requestBody)
	if err != nil {
		log.Fatalf("error: %s\n", err.Error())
		return
	}

	var body []byte
	if body, err = io.ReadAll(res.Body); err != nil {
		log.Fatalf("error: %s\n", err.Error())
		return
	}

	var postResp PostResponse
	if err := json.Unmarshal(body, &postResp); err != nil {
		log.Fatalf("error: %s\n", err.Error())
		return
	}

	fmt.Printf("%+v\n", postResp)
}
```


#### Timeout request

```go
client := http.Client{
	Timeout: time.Second * 5,
}

res, err := client.Get(url)
```
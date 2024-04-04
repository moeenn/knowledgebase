```go
package main

import (
  "log"
  "os"
)

func main() {
  logger := log.New(os.Stdout, "[debug] ", log.Ldate|log.Ltime)

  logger.Println("Starting program...")
  logger.Println("Performing calculations")
  logger.Println("Cleaning up...")
}


/**
 *  [debug] 2022/02/05 13:08:35 Starting program...
 *  [debug] 2022/02/05 13:08:35 Performing calculations
 *  [debug] 2022/02/05 13:08:35 Cleaning up…
 */
```


#### Structured logging

```go
package main

import (
	"log/slog"
	"os"
)

func main() {
	logger := slog.New(slog.NewJSONHandler(os.Stderr, nil))

	logger.Debug("this is a debug message")
	logger.Info("this is an info message")
	logger.Warn("this is a warning message")
	logger.Error("this is an error message")
}
```


##### Contextual Awareness
Structured logger is smart enough to recognise arbitrary key-value pairs and print them as such.

```go
logger.Info(
	"this is a debug message",
	"method", "GET",
	"url", "http://site.com",
)

/* output
{
  "time":"2023-12-29T20:50:07.238087+05:00",
  "level":"INFO",
  "msg":"this is a debug message",
  "method":"GET",
  "url":"http://site.com"
}
*/
```


#### Logging objects

```go
package main

import (
	"log/slog"
	"os"
)

type User struct {
	Id    int    `json:"id"`
	Name  string `json:"name"`
	Email string `json:"email"`
}

func main() {
	logger := slog.New(slog.NewJSONHandler(os.Stderr, nil))

	user := User{
		Id:    10,
		Name:  "Admin",
		Email: "admin@site.com",
	}

	logger.Info(
		"logged-in user visited site",
		"user", user,
	)
}
```
```go
package main

import (
  "fmt"
  "os"
  "strings"
)

func check(e error) {
  if e != nil {
    panic(e)
  }
}

func main() {
  var err error

  err = os.Setenv("LINUX", "Ubuntu")
  check(err)
  fmt.Println("LINUX: ", os.Getenv("LINUX"))

  /* check if env Variable is set */
  if system := os.Getenv("SYSTEM"); len(system) > 0 {
    fmt.Println("SYSTEM: ", system)
  }


  /* get all environment variables */
  for _, e := range os.Environ() {
    var pair []string = strings.Split(e, "=")
    fmt.Println(pair)
  }
}
```


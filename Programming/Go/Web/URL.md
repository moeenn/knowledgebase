```
postgres://user:pass@host.com:5432/path?k=v#f

postgres -> scheme
user:pass -> user
host.com:5432 -> host
/path -> path
k=v -> query params
f -> fragment
```

```go
package main

import (
  "fmt"
  "net" // for splitting host and port
  "net/url"
)

func check(e error) {
  if e != nil {
    panic(e)
  }
}

func main() {
  urlString := "postgres://user:pass@host.com:5432/path?k=v&a=b#f"

  u, err := url.Parse(urlString)
  check(err)

  fmt.Printf("%v\n", u)
  fmt.Println(u.Scheme, u.User, u.Host, u.Path, u.RawQuery, u.Fragment)

  // get server port
  host, port, _ := net.SplitHostPort(u.Host)
  fmt.Println(host, port)

  // parse query strings
  queryMap, _ := url.ParseQuery(u.RawQuery)
  for key, value := range queryMap {
    fmt.Println(key, value[0])
  }
}

/*
postgres://user:pass@host.com:5432/path?k=v&a=b#f
postgres user:pass host.com:5432 /path k=v&a=b f
host.com 5432
k v
a b
*/
```

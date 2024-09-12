```go
package main

import (
  "fmt"
  "regexp"
)

func main() {
  pattern := regexp.MustCompile(`<[a-zA-Z\s=\-_\'\"]*[^/]>`)

  // return the first match
  result := pattern.FindString("<div><hr><something>")

  // return all matches as a slice. -1 is the max results to return
  resultSlice := pattern.FindAllString("<div><hr><something>", -1)

  // replace patterns
  replaced := pattern.ReplaceAllString("<Heading>This is a heading</Heading>", "<h1 class=\"mt-1\">")

  fmt.Println(result, resultSlice, replaced)
}

/*
<div> 
[<div> <hr> <something>] 
<h1 class="mt-1">This is a heading</Heading>
*/
```

**Important**: Encase REGEXP in Backticks instead of Double Quotes to minimize the number of escapes required.

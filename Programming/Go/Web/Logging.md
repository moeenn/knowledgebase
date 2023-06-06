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


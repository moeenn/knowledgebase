##### Reading full file contents

```go
// content is of type []byte
content, err := os.ReadFile("./sample.txt")
if err != nil {
	fmt.Printf("error: %s\n", err.Error())
	return
}
```



```go
package main

import (
  "fmt"
  "os"
)

func check(e error) {
  if e != nil {
    panic(e)
  }
}

func main() {
  fileLocation := "./sample"

  // read entire file
  data, err := os.ReadFile(fileLocation)
  check(err)
  fmt.Println(string(data))

  // keep file open until end of scope
  file, err := os.Open(fileLocation)
  check(err)
  defer file.Close()

  // read 20 bytes from the file
  block := make([]byte, 20)
  bytesRead, err := file.Read(block)
  check(err)
  fmt.Printf("Position: %v\nBlock: %v\n", bytesRead, string(block))

  // set current read position
  newPos, err := file.Seek(20, 0)
  check(err)
  fmt.Printf("Cursor Position: %d\n", newPos)

  // read from new cursor position
  bytesRead, err = file.Read(block)
  check(err)
  fmt.Printf("Bytes Read: %v\nBlock: %v\n", bytesRead, string(block))
}
```


##### Writing files
```go
filePath := "./dir/sample2"
data := []byte("This line will be written to file")
err := os.WriteFile(filePath, data, 0640)
check(err)
```

- `WriteFile` will create the file if it doesn’t exist. If it exists, the contents will be overwritten
- Data must be provided in form of a Byte Slice, we cast as string into a Byte Slice
- `0640` is the Chmod permission representing file access restrictions  
- `WriteFile` will fail if the location where file is to be created doesn’t exist

```go
package main

import (
  "os"
)

func check(e error) {
  if e != nil {
    panic(e)
  }
}

func main() {
  filePath := "./dir/sample2"

  file, err := os.OpenFile(filePath,
    os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0640)
  check(err)
  defer file.Close()

  data := "This line will be written to file\n"
  _, err = file.WriteString(data)
  check(err)
}
```

**Note**: Unlike `ioutil.WriteFile`, `os.OpenFile` takes the data in form of a `string`.


##### Files modes
|       Mode | Description                                 |
| ---------: | :------------------------------------------ |
| `O_RDONLY` | Read-only                                   |
| `O_WRONLY` | Write-only                                  |
|   `O_RDWR` | Read-write                                  |
| `O_APPEND` | Append data to end of File                  |
| `O_CREATE` | Create new File if it doesn’t already exist |
|   `O_SYNC` | Open File for Synchronous I/O               |


---

#### Directories

##### Listing Directory Content
```go
package main

import (
  "fmt"
  "io/ioutil"
)

func main() {
  dirPath := "./dir"
  files, err := ioutil.ReadDir(dirPath)
  check(err)

  for _, file := range files {
    fmt.Printf("Name: %10v Size: %10v bytes Dir: %10v\n",
      file.Name(),
      file.Size(),
      file.IsDir(),
    )
  }
}

/*
Name: another.pdf Size:          0 bytes Dir:      false
Name:     nested Size:       4096 bytes Dir:       true
Name:     sample Size:        446 bytes Dir:      false
*/
```


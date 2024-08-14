
Type: Structure

```go
import (
	"fmt"
	"log"
)

type DataSource interface {
	WriteData(string)
	ReadData() string
}

// implements DataSource
type FileDatasource struct {
	content string
}

func (f *FileDatasource) WriteData(data string) {
	f.content += data
}

func (f FileDatasource) ReadData() string {
	return f.content
}

// implements DataSource
type DecoratedFileDatasource struct {
	file *FileDatasource
}

func (f *DecoratedFileDatasource) WriteData(data string) {
	log.Println("writing to file")
	f.file.content += data
}

func (f DecoratedFileDatasource) ReadData() string {
	log.Println("reading from file")
	return f.file.content
}

func main() {
	file := &FileDatasource{""}
	decoratedFile := DecoratedFileDatasource{file}

	decoratedFile.WriteData("Some content")
	fmt.Println(decoratedFile.ReadData())
}
```
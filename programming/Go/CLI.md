#### TODO

- [ ] `github.com/urfave/cli/v2`


---

#### Flags

```go
import (
	"flag"
	"fmt"
)

func main() {
  name := flag.String("name", "", "name of the user")
  age := flag.Int("age", 0, "age of the user")
  approved := flag.Bool("approved", false, "is the user approved")
  flag.Parse()

  fmt.Printf("Name: %s, Age: %d, Approved: %v\n", *name, *age, *approved)
}
```


---
#### Colored output

```go
import (
	"github.com/fatih/color"
)

func main() {
	color.Cyan("Simple cyan text")
	color.Green("Simple green text")

	// text interpolation
	color.Red("Simple red %s", "interpolated text")

	// combining styles
	c := color.New(color.BgRed, color.FgBlack, color.Bold)
	c.Print(" Red background with black text ")
}
```
#### TODO

- [ ] `flag` package
- [ ] `github.com/urfave/cli/v2`


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
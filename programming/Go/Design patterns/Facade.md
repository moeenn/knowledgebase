
This pattern aims to simplify the interface of other entities.

```go
type Logger interface {
	Log(out io.Writer, level string, message []byte)
}

type RawLogger struct{}

func (l RawLogger) Log(out io.Writer, level string, message []byte) {
	fmt.Fprintf(out, "%s - %s\n", level, message)
}

type LoggerFacade struct {
	out      io.Writer
	instance Logger
}

func NewLogger(out io.Writer, instance Logger) *LoggerFacade {
	return &LoggerFacade{
		out:      out,
		instance: instance,
	}
}

func (l LoggerFacade) Info(message string) {
	l.instance.Log(l.out, "info", []byte(message))
}

func (l LoggerFacade) Warn(message string) {
	l.instance.Log(l.out, "warn", []byte(message))
}

func main() {
	logger := NewLogger(os.Stdout, &RawLogger{})
	logger.Info("Some random message")
	logger.Warn("Some warning")
}
```

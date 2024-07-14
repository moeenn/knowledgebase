
Type: Behavioral

```go
type Location struct {
	Lat, Lng float64
}

func (l Location) ToString() string {
	return fmt.Sprintf("(%f, %f)", l.Lat, l.Lng)
}

type RouteStrategy interface {
	execute(start, end Location)
}

type WalkStrategy struct{}

func (w WalkStrategy) execute(start, end Location) {
	fmt.Printf("Walking from %s to %s\n", start.ToString(), end.ToString())
}

type DriveStrategy struct{}

func (d DriveStrategy) execute(start, end Location) {
	fmt.Printf("Driving from %s to %s\n", start.ToString(), end.ToString())
}

type RouteContext struct {
	strategy RouteStrategy
}

func NewRouteContext(strategy RouteStrategy) *RouteContext {
	return &RouteContext{strategy}
}

func (ctx *RouteContext) SetStrategy(strategy RouteStrategy) {
	ctx.strategy = strategy
}

func (ctx RouteContext) ExecuteStrategy(start, end Location) {
	ctx.strategy.execute(start, end)
}

func main() {
	driveStrategy := DriveStrategy{}
	ctx := NewRouteContext(driveStrategy)
	start := Location{30.44, 50.66}
	end := Location{70.31, 10.67}
	ctx.ExecuteStrategy(start, end)

	walkStrategy := WalkStrategy{}
	ctx.SetStrategy(walkStrategy)
	ctx.ExecuteStrategy(start, end)
}
```
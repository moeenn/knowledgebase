
Type: Creation

```go
package singleton

import "sync"

type singleton map[string]string

var (
	once     sync.Once
	instance singleton
)

func New() singleton {
    // anonymous function will only be called once
	once.Do(func() {
		instance = make(map[string]string)
	})

	return instance
}
```

```go
store := singleton.New()
store["Pakistan"] = "Islamabad"
store["China"] = "Biejing"

storeTwo := singleton.New()
fmt.Println(storeTwo["Pakistan"]) // Islamabad
```

**Note**: Singleton pattern represents a global state and most of the time reduces testability.
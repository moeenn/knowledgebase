```go
// numbers.go 
package numbers

func IsPrime(n int) bool {
  if n == 0 || n == 1 {
    return false
  }

  for i := 2; i <= n/2; i++ {
    if n%i == 0 {
      return false
    }
  }

  return true
}
```

```go
// numbers_test.go 
package numbers

import (
  "testing"
)

type testCase struct {
  Input  int
  Result bool
}

func TestIsPrime(t *testing.T) {
  testCases := []testCase{
    {Input: 2, Result: true},
    {Input: 9, Result: false},
    {Input: 13, Result: true},
  }

  for _, testCase := range testCases {
    got := IsPrime(testCase.Input)
    if got != testCase.Result {
      t.Errorf("expected: %v, got: %v", testCase.Result, got)
    }
  }
}
```


##### Running the tests

```bash
$ go test -v ./...
```

- The package name for the file and the main file must be the same
- The name of the file containing tests should be `<package>_test.go`
- The names of the test functions must start with `Test`


##### Note on `-v` flag

Sometimes we may rely on `printf-debugging` to check why our tests are failing. If the `-v` flag is not provided then none of the `fmt.Print` or `log.Print` related output will be displayed. It's almost always a good idea to pass the `-v` flag because it does print other useful information as well. 
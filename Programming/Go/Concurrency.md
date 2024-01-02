#### Channels

```go
func main() {
	valueChan := make(chan int /*, optional buffer length here */)

	go func() {
		for i := 0; i < 10; i++ {
			/**
			 * sending value into unbuffered channel will block until there is
			 * an active receiver
			 */
			valueChan <- i
		}

		/* the sender must always close the channel */
		close(valueChan)
	}()

	/* receive values until channel is closed */
	for value := range valueChan {
		fmt.Printf("value: %d\n", value)
	}
}
```


#### Channel Sync: Select

```go
import (
	"fmt"
	"time"
)

func main() {
	chanOne := make(chan int)
	chanTwo := make(chan int)

	go func() {
		for i := 1; i <= 10; i++ {
			time.Sleep(time.Second / 2)
			chanOne <- i
		}
		/* Don't close the channel here */
	}()

	go func() {
		for i := 100; i <= 200; i += 10 {
			time.Sleep(time.Second)
			chanTwo <- i
		}
		/* Don't close the channel here */
	}()

	/* we expect to receive only 20 messages total on both channels */
	for i := 0; i < 20; i++ {
		/**
		 * select will wait for incoming messages on these two channels.
		 * Select block exits after in two situations
		 * - it receives the first message from any of the two channels.
		 * - any of the two channels closes.
		 */
		select {
		case one := <-chanOne:
			fmt.Printf("chanOne: %d\n", one)

		case two := <-chanTwo:
			fmt.Printf("chanTwo: %d\n", two)
		}
	}

	close(chanOne)
	close(chanTwo)
}
```


```go
package main

import (
  "fmt"
)

func main() {
  // create channels
  messages := make(chan string)
  done := make(chan bool)

  // run goroutines
  go routine_a(messages)
  go routine_b(messages, done)

  // block the main goroutine until value is received
  <-done
}

func routine_a(channel chan string) {
  // send value into the value
  channel <- "This is a message from the goroutine"
}

func routine_b(channel chan string, flag chan bool) {
  // receive value from the channel
  incoming := <-channel
  fmt.Println(incoming)
  flag <- true
}

// This is a message from the goroutine
```


---

#### Wait groups
```go
package main

import (
  "fmt"
  "sync"
)

func main() {
  messages := make(chan string)

  // configure wait group to wait to two concurrent tasks
  var wait_group sync.WaitGroup
  wait_group.Add(2)

  go func() {
    // mark task as complete
    defer wait_group.Done()
    routine_a(messages)
  }()

  go func() {
    defer wait_group.Done()
    routine_b(messages)
  }()

  // wait for running tasks to complete
  wait_group.Wait()
}

func routine_a(channel chan string) {
  channel <- "This is a message from the goroutine"
}

func routine_b(channel chan string) {
  incoming := <-channel
  fmt.Println(incoming)
}
```


---

#### Ranging over Channel Messages
- Channels must always be closed by senders (and not receivers) because we cannot send over closed channels
- We can only range over channels which will be closed by senders

```go
package main

import (
  "fmt"
)

func main() {
  msgs := make(chan string)

  go action("Message", msgs)
  go action("Response", msgs)

  for msg := range msgs {
    fmt.Println(msg)
  }
}

func action(name string, c chan<- string) {
  for i := 0; i < 10; i++ {
    c <- fmt.Sprintf("%d - %s", i, name)
  }

  // sender must close the channel, never the receiver
  close(c)
}
```


---

#### Implementing generators 
Considering how Python uses generators, for iterating over a large number of values without running into memory usage issues. We can implement a similar pattern in Go using Channels

```go
func iterate(n int) chan int {
  c := make(chan int)

  go func() {
    for i := 0; i < n; i++ {
      c <- i
    }

    close(c)
  }()

  return c
}

func main() {
  for n := range iterate(1000) {
    fmt.Printf("%d\t", n)
  }
}
```

**Note**: When we range over incoming channel values, we must ensure that the sender closes the channel when it is done sending values. The sender must always be responsible for closing the channel and if the channel is left open, it will result in a deadlock; The receiver will keep waiting for incoming values after the sender is done sending values.


---

#### Worker Pools

```go
package main

import (
  "fmt"
  "time"
)

type Entry struct {
  Id     int
  Result bool
}

func createData() []Entry {
  data := []Entry{
    {Id: 1, Result: false},
    {Id: 2, Result: false},
    {Id: 3, Result: false},
    {Id: 4, Result: false},
    {Id: 5, Result: false},
    {Id: 6, Result: false},
    {Id: 7, Result: true},
    {Id: 8, Result: false},
  }

  return data
}

func task(entry Entry) Entry {
  time.Sleep(time.Second)
  fmt.Printf("Processed entry: %v\n", entry)
  return entry
}

func executor(entries []Entry, maxWorkers int, results chan<- Entry) {
  sem := make(chan int, maxWorkers)
  for _, entry := range entries {
    go func(entry Entry) {
      sem <- 1
      result := task(entry)
      results <- result
      <-sem
    }(entry)
  }
}

func main() {
  entries := createData()
  maxWorkers := 2
  results := make(chan Entry, maxWorkers)

  executor(entries, maxWorkers, results)

  for i := 0; i < len(entries); i++ {
    result := <-results
    fmt.Printf("Result: %v\n", result)
  }
}
```

**Note**: The purpose of the Semaphore (i.e. `sem`) is to coordinate and only allow max number of operation to happen concurrently i.e. `maxWorkers`.

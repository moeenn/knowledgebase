```bash
# language server
$ go install golang.org/x/tools/gopls@latest
```

##### Modules
It is no longer compulsory to place your project files inside the directories specified above. Current versions of Go have introduced Go Modules. Inside any normal folder in the system, we can execute the following command to create a Go Module.

```bash
$ go mod init <program_name>
```


##### Install Project Dependencies
When we run a project, Go detects all dependencies of the project. We can install all project dependencies using the following command. The following also looks for any unused dependencies and removes them.

```bash
$ go mod tidy
```


---

#### Hello world
```go
package main


import (
  "fmt"
)

func main() {
  fmt.Println("Hello World")
}
```


---

#### Importing Libraries
A single library can be imported as it has been in the hello world program above. If we need to import multiple libraries we should use the Go convention

```go
/* not the Go convention */
import "fmt"
import "time"

/* Go convention */
import (
  "fmt"
  "time"
)
```

**Note**: If we import a library and don’t use it in our code, the GoLang compiler will raise an error preventing compilation. 


---

#### Packages
You may have noticed the first line in our Hello World program: Every program must have at least one main package. **We cannot have more than one package in a single directory**.

```
main.go
pkg/
  user/
    user.go
```

```go
/* user.go */
package user

import (
  "encoding/json"
)

type User struct {
  Id       uint   `json:"id"`
  Name     string `json:"name"`
  Email    string `json:"email"`
  Password string `json:"-"`
}

func (user User) Serialize() (string, error) {
  encoded, err := json.Marshal(user)
  if err != nil {
    return "", err
  }

  return string(encoded), nil
}

func New(name, email string) User {
  return User{
    Id:       300,
    Name:     name,
    Email:    email,
    Password: "password",
  }
}
```

```go
/* main.go */
package main

import (
  "fmt"
  "os"
  "sandbox/pkg/user"
)

func main() {
  user := user.New("Sample", "sample@site.com")
  encoded, err := user.Serialize()
  if err != nil {
    fmt.Fprintf(os.Stderr, "error: %v\n", err)
    os.Exit(1)
  }

  fmt.Println(encoded)
}
```


---

##### Double quotes vs. Single Quotes
In Go, double quotes are used to define strings and import modules. This is strictly enforced so using single-quotes in these cases will result in compilation errors.

The names of Imported Libraries can also be Aliased

```go
/* import strings as s */
import s "strings"
```


##### Comments
```go
// single line comment

/**
 *  Comment block
 *
 */
```


##### Logical operators
```go
fmt.Println(true && false)	/* false */
fmt.Println(true || false)	/* true  */ 
fmt.Println(!true)		    /* false */ 
```


##### Data types
| Operator | Description |  
| -------: | :------ |  
| `int, int8, int16, int32, int64` | Integers |  
| `uint, uint8, uint16, uint32, uint64` | Unsigned integers |
| `float, float32, float64` | Floating point numbers |
| `bool` | Boolean value | 
| `string` | Stream of characters | 
| `rune` | Rune is used to represent Characters. It is an alias for `int32` |
| `byte` | Byte is an alias for `uint8` | 


##### Defining Variables
```go
/* defining and initializing without specifying the data type */
a := 300         
var b = 30.95    

/* specifying the data type */
var c string = "This is a string"

/* defining but not initializing */
var d bool

/* defining multiple variables at the same time */
var e, f int = 32, 64 
```


##### Multi-line Strings
```go
fmt.Println(`
  This is a simple
  multiline message
  -- Good Bye`)
```


##### Constants
Constants are defined the same way as variables. We use the keyword `const` instead of `var`. Constants are immutable.  

```go
const name string = "Connor Kenway"
```



##### Find the type of a variable
```go
var name string = "Kalahari"

func typeof(i interface{}) {
  fmt.Printf("%T\n", i)
}

/* string */ 
```

```go
fmt.Printf("My name is %v and I am %v years old.", "User", 27)
fmt.Printf("It is %v that I am a programmer", true)
```


##### Converting Numbers to Strings
```go
import (
  "fmt"
  "strconv"
)

func main() {
  num := 30
  fmt.Printf("%v, %T\n", num, strconv.Itoa(num))
}

/* 30, string */ 
```


##### Type Casting
Go doesn’t perform any implicit type conversions. All conversions must be explicit. Variables can be casted to any compatible data type, primitive or custom. 

We can use the name of the data type as a function call for casting data types.

```go 
var num uint32 = 400
num2 := int64(num)
typeof(num2)

/* int64 */ 
```


---

#### Byte Slices
As mentioned earlier, Byte is simply an Alias for the Uint8 Primitive Data Type. Often functions return data in the form of Byte Slices. Here is what they look like

```go
[76 111 114 101 109 32 105 112 115 117 109 32 100 111 108]
```

```go
data, _ := ioutil.ReadFile("./dir/sample")

/* method one */
fmt.Printf("%s\n", data)

/* method two */
fmt.Println(string(data))
```


##### String to Byte Slice
```go
/* cast string as byte slice */
example := []byte("This is a simple Message")
fmt.Printf("%s\n", example)
```


---

#### String Methods
```go
package main

import (
  "fmt"
  "strings"
)

func main() {
  fmt.Println("Contains:  ", strings.Contains("test", "es"))
  fmt.Println("ToLower:   ", strings.ToLower("TEST"))
  fmt.Println("ToUpper:   ", strings.ToUpper("test"))
  fmt.Println("Count:     ", strings.Count("test", "t"))
  fmt.Println("HasPrefix: ", strings.HasPrefix("test", "te"))
  fmt.Println("HasSuffix: ", strings.HasSuffix("test", "st"))
  fmt.Println("Index:     ", strings.Index("test", "t"))
  fmt.Println("Split:     ", strings.Split("a-b-c-d-e", "-"))
  fmt.Println("Join:      ", strings.Join([]string{"a", "b"}, "-"))
  fmt.Println("Repeat:    ", strings.Repeat("a", 5))
  fmt.Println("Replace:   ", strings.Replace("foo", "o", "0", -1))
  fmt.Println("Replace:   ", strings.Replace("foo", "o", "0", 1))
  fmt.Println("TrimSpace: ", strings.TrimSpace("   test    "))
}

/*
Contains:   true
ToLower:    test
ToUpper:    TEST
Count:      2
HasPrefix:  true
HasSuffix:  true
Index:      0
Split:      [a b c d e]
Join:       a-b
Repeat:     aaaaa
Replace:    f00
Replace:    f0o
TrimSpace:  test
*/
```


##### String interpolation
```go
func greet(name string) string {
  return fmt.Sprintf("Hello %v, Welcome to our website!", name)
}
```


##### String Formatting
| Placeholder | Description |  
| -------: | :------ |  
| `%v` | Infer and Print any Data type |  
| `%+v` | Print Struct with field names |
| `%d` | Decimal Number i.e. Base-10 representation |
| `%b` | Binary Number i.e. Base-2 Representation  | 
| `%x` | Hexadecimal Number i.e. Base-16 | 
| `%c` | Character representation of Number |
| `%f` | Floating Point Number |
| `%e` | Exponent Notation |
| `%s` | Strings |
| `%p` | Pointers |
| `%6d` | Set Decimal Width to 6 characters, Right Aligned |
| `%-5.2f` | Set Float width to 5 with 2 decimal places, Left Aligned |


---

#### Loops
The only keyword related to Loops that exists in Go is `for`.

```go
/* for loop */
for i:= 0; i <= 10; i++ {
    fmt.Println(i)
}

/* while loop */
i := 0
for i <= 10 {
  fmt.Println(i)
  i++
}

/* infinite loop*/
for {
  fmt.Println("Infinite Loop")
}

/* looping through arrays, slices, maps */
names := []string{"Batman", "Ironman", "Superman"}
for _, name := range(names) {
  fmt.Println(name)
}
```


---

#### Break and Continue
The `break` and `continue` keywords work exactly the same way as C / C++
- `break` ends the loop immediately
- `continue` skips over the rest of the code in the loop and goes to the next iteration of the loop


---

#### Control-flow
```go
marks := 90

if marks < 40 {
  fmt.Println("F: Fail")
} else if marks < 70 {
  fmt.Println("B: Average")
} else if marks <= 100 {
  fmt.Println("A: Excellent")
} else {
  fmt.Println("Invalid Marks")
}

/* A: Excellent */ 
```

GoLang supports for-loop style preconditions in if statements as well. This can be helpful in making the code easier to understand. 

```go
if i := 30; i < 100 {
  fmt.Println("30 is less than 100")
}
```

**Note**: In the above example, the scope of `i` is limited to the block of If-statement.


##### Switch Statements
```go
option := 4

switch option {
  case 1:
    fmt.Println("One")
        
  case 2, 3:
    fmt.Println("Two or Three")
        
  case 4:
    fmt.Println("Four")
        
  default:
    fmt.Println("Invalid Input")
}

/* Four */ 
```

One of the limitations of switch statements in C / C++ is that we cannot use conditions. In Go, any nested if statement can be written as a switch statement.

```go
marks := 50

switch {
  case marks < 40:
    fmt.Println("F: Fail")
    
  case marks < 70:
    fmt.Println("B: Average")
        
  case marks <= 100:
    fmt.Println("A: Excellent")
    
  default:
    fmt.Println("Invalid Marks")
}
/* B: Average*/ 
```


---

#### Arrays
```go
/* declare an empty array */
var myArray [5]int
fmt.Println(myArray)              

/* [0 0 0 0 0] */

/* access / change values from array */
myArray[0] = 300
myArray[4] = 220
fmt.Println(myArray)             

/* [300 0 0 0 220] */

/* initialize array with values */
myArray2 := [5]int{ 23, 34, 29, 45, 56 }
fmt.Println(myArray2)           

/* [23 34 29 45 56] */
```

```go
arraySize := len(myArray)
```

```go
/* declaring without values */
var myArr [3][3]int
fmt.Println(myArr)
/* [[0 0 0] [0 0 0] [0 0 0]] */

/* declaring with values */
myArray := [2][2]int {{ 30, 20 }, { 10, 40}}
fmt.Println(myArray)    
/* [[30 20] [10 40]] */
```


---

#### Slices
Slices are like arrays but they are dynamic in size. Unlike an array we don’t specify the size / length of a slice when we initialize it. 

```go
/* declaration */
a := []int{}

/* declaration and initialization */
b := []int{10, 20, 30}

/* add elements */
my_slice = append(my_slice, 54, 32, 65)
```

Reason why they are called slices is because we can slice through them like Python slices

```go
/* my_slice := [54 32 65 20 35 15 39] */

my_slice[1:3]		/* [32 65] */
my_slice[:4]		/* [54 32 65 20] */ 
my_slice[4:]		/* [35 15 39] */
```


##### Removing element from a slice
```go
myArray := []int{1, 2, 3, 4, 5, 6, 7}

/* index value to be removed */
const remID int = 3

myArray = append(myArray[:remID], myArray[remID+1:]...)
fmt.Println(myArray)
```

In our example we slice up to the desired index (up to and not including) and unpack all the elements of the slice after the desired index. After the unpacking instructions will look like this behind the scenes

```go
myArray = append(myArray[:remID], 5, 6, 7)
```

**Note**: `…` are called the Spread Operator


---

#### Functions
```go
func myFunction(a float64, b float64) float64 {
  return a + b
}
```

Before the curly braces we specify the return type of the function. This is only required if the function actually returns anything.

```go
func myFunction(a, b float64) float64 {
  return a + b
}
```

```go
func myFunction(a, b float64) (float64, float64) {
  return a+10, b+10
}
```


##### Variadic Functions
These are functions that take an arbitrary number of values as arguments. 

```go
func sum(nums ...int) int {
  result := 0
  
  for _, num := range nums {
    result += num
  }
  return result
}

func main() {
  fmt.Print(sum(1,2,3,4)) 
}

/* 10 */
```

```go
myNumbers := []int{10, 20, 30, 40}

// passing a slice to variadic function
fmt.Print(sum(myNumbers...))	
```


##### Higher order Functions
```go
type wrappedFunc func (uint64) uint64
```


---

#### Maps
```go
nationality := map[string]string {}

/* add key values */
nationality["Alice Eve"] = "British"
nationality["George Clooney"] = "American"
nationality["Trevor Noah"] = "South African"


/* accessing a value using key */
fmt.Println(nationality["Alice Eve"])
```

```go
nationality := map[string]string{
  "Alice Eve": "British", 
  "Trevor Noah": "South African",
}
```

```go
// Deleting values from Map
delete(nationality, "George Clooney")
```


---

#### Range
```go
myNumbers := []int{12, 23, 34, 45, 56, 67, 78}
for index, num := range myNumbers{
  fmt.Printf("%d %d\n", index, num)
}
```

```go
for name, nation := range nationality {
  fmt.Println(name, nation)		
}
```


---

#### Pointers
```go
var a int = 30
var b *int = &a                

fmt.Println("a:", a)    // 30
fmt.Println("b:", b)    // 0xc4200120c8
fmt.Println("*b:", *b)  // 30 i.e. dereferenced value

*b = 10                 // dereference and change value
fmt.Println("a:", a)    // 10
fmt.Println("b:", b)    // 0xc4200120c8
fmt.Println("*b:", *b)  // 10
```


---

#### Closures
```go
func adder() func(int) int {
  sum := 0
  return func(x int) int {
    sum += x
    return sum
  }
}

func main() {
  sum := adder()

  for i := 1; i <= 5; i++ {
    fmt.Println(sum(i))
  }
}

/* 1 3 6 10 15 */
```

```go
func fibs() func() int {
  val1 := 1
  val2 := 1
  tmp := 0

  return func() int {
    tmp = val1 + val2
    val1 = val2
    val2 = tmp

    return val2
  }
}

/* 1 2 3 5 8 13 21 34 55 89 */ 
```


---

#### Structs
```go
type Car struct {
  brand string
  year uint64
  electric bool
}
```

**Note**: A `struct` field is only exported outside the package if it Begins with a Capital Alphabet. In the above Car Struct, none of the Fields are exported, i.e. all fields are private.

```go
/* quicker approach */
myCar2 := Car{"Honda", 2010, true}

/* more explicit */
myCar := Car{
  brand:    "toyota",
  year:     2005,
  electric: false,
}

/* calling the attributes */
fmt.Println(myCar.brand, myCar2.electric)
```


##### Anonymous Structs
```go
Employee := struct {
    Name string
    FullTime bool
}{
    Name: "Random user",
    FullTime: false,
}
```


##### Struct methods
There are two types of methods in Go
- Value Receivers - They Get the values but cannot modify them
- Pointer Receivers - They Set the values through pointers

```go
type Employee struct {
  Name string
  Salary uint
}

/* value receiver methods */
func (e Employee) Display() {
  fmt.Printf("Employee:: Name: %v, Salary: %v\n", e.Name, e.Salary)
}

func (e Employee) Repr() string {
  return fmt.Sprintf("Employee:: Name: %v, Salary: %v", e.Name, e.Salary)
}

/* pointer receiver methods */
func (e *Employee) UpdateSalary(newSalary uint) {
  e.Salary = newSalary
}

func main() {
  e := Employee{
    Name: "Sana Ullah",
    Salary: 30000,
  }

  e.Display()
  fmt.Println(e.Repr())

  e.UpdateSalary(40000)
  e.Display()
}
```


##### Methods on Primitive Types
Go enforces the rule that the Data Type and all its methods must be defined in the same package. Due to  this rule we cannot directly implement methods on Primitive Data Types. However, we have the option to derive custom data types from primitive data types

```go
type str string

func (s str) ToUpperCase() string {
  normal_string := string(s)
  return strings.ToUpper(normal_string)
}

func main() {
  s := str("This is a mixed case strinG")
  fmt.Println(s.ToUpperCase())
}
```


---

#### Interfaces
Go doesn’t have Generics / Templates like C++. Go is strongly Typed so we also don’t have the option of Duck Typing. The solution is to use Interfaces. An interface details a collection of methods. 

```go
package main

import (
  "fmt"
)

type Employee struct {
  age int
}

func (e Employee) display() string {
  return fmt.Sprintf("Name: %v\n", e.age)
}

type Vine struct {
  vintage int
}

func (v Vine) display() string {
  return fmt.Sprintf("Vintage: %v\n", v.vintage)
}

func details(i interface{ display() string }) {
  fmt.Print(i.display())
}

func main() {
  var emp Employee = Employee{30}
  details(emp)

  var vine Vine = Vine{1960}
  details(vine)
}
```


---

#### Enums
```go
package direction

type Direction uint

const (
  LEFT Direction = iota
  RIGHT
  UP
  DOWN
)
```

```go
package entity

type Entity struct {
  X uint
  Y uint
}

func (e *Entity) Move(d direction.Direction) error {
  /***/
}
```


---

#### Error Handling

```go
package main

import (
  "fmt"
  "errors"     
)

func task(num *int) error {
  if *num == -1 {
    return errors.New("Cannot process -1")
  }
  *num = *num * *num * *num
  return nil
}

func main() {
  num := 4
  err := task(&num)

  if err != nil {
    fmt.Println(err)
  }

  fmt.Println(num)
}
```


---

#### Sorting

```go
package main

import (
  "fmt"
  "sort"
)

func main() {
  nums := []int{23, 45, 21, 87, 45, 82, 17}
  sort.Ints(nums)
  fmt.Println(nums)

  strings := []string{"bravo", "alpha", "delta", "charlie"}
  sort.Strings(strings)
  fmt.Println(strings)

  flag := sort.IntsAreSorted(nums)
  fmt.Println(flag)

  flag = sort.StringsAreSorted(strings)
  fmt.Println(flag)
}

/*
[17 21 23 45 45 82 87]
[alpha bravo charlie delta]
true
true
*/
```

Go also provides a way to do custom sorts. Following code sorts by length an array of Strings

```go
package main

import (
  "fmt"
  "sort"
)

type Data []string

func (d Data) Len() int {
  return len(d)
}

func (d Data) Swap(a, b int) {
  d[a], d[b] = d[b], d[a]
}

func (d Data) Less(a, b int) bool {
  return len(d[a]) < len(d[b])
}

func main() {
  msgs := []string{"This is", "a", "messagess"}
  sort.Sort(Data(msgs))
  fmt.Println(msgs)
}
```


---

#### Defer
Defer is used to postpone the execution of instructions till either
- End of the block
- Error in the block

This means the deferred statement inside a function will be executed when the entirety of the function is executed OR the program runs into errors during execution of the function.

This is useful when resources need to be released no matter the successful execution of the function or otherwise, e.g. closing connections to the DB, closing open files, releasing threads etc.

```go
func foo() {
  fmt.Println("Deferred Function")
}

func main() {
  defer foo()

  for i := 0; i <= 100; i++ {
     fmt.Print(i, "\t")
  }
}
```

In the above example, the program will count up to 100 and then run the foo function.


#### Hello world
Complete the code to make the program print "Mary is 20 years old" to standard output

```kotlin
fun main() {
    val name = "Mary"
    val age = 20
    println("$name is $age years old")
}
```


---

#### Basic types
Explicitly declare the correct type for each variable

```kotlin
fun main() {
    val a: Int = 1000
    val b: String = "log message"
    val c: Double = 3.14
    val d: Long = 100_000_000_000
    val e: Boolean = false
    val f: Char = '\n'
}
```

**Note**: Use `3.14f` to declare `c` as `Float`


---

#### Collections

You have a list of “green” numbers and a list of “red” numbers. Complete the code to print how many numbers there are in total.

```kotlin
fun main() {
    val greenNumbers = listOf(1, 4, 23)
    val redNumbers = listOf(17, 2)
    val totalCount = greenNumbers.count() + redNumbers.count()
    println(totalCount)
}
```

You have a set of protocols supported by your server. A user requests to use a particular protocol. Complete the program to check whether the requested protocol is supported or not (`isSupported` must be a `Boolean` value).

```kotlin
fun main() {
    val SUPPORTED = setOf("HTTP", "HTTPS", "FTP")
    val requested = "smtp"
    val isSupported = requested.uppercase() in SUPPORTED
    println("Support for $requested: $isSupported")
}
```

Define a map that relates integer numbers from 1 to 3 to their corresponding spelling. Use this map to spell the given number.

```kotlin
fun main() {
    val number2word = mapOf(1 to "one", 2 to "two", 3 to "three")
    val n = 2
    println("$n is spelt as '${number2word[n]}'")
}
```


---

#### Control-flow

Using a `when` expression, update the following program so that when you input the names of GameBoy buttons, the actions are printed to output.

```kotlin
fun main() {
    val button = "A"

    println(
        when (button) {
            "A" -> "Yes"
            "B" -> "No"
            "X" -> "Menu"
            "Y" -> "Nothing"
            else -> "There is no such button"
        }
    )
}
```

You have a program that counts pizza slices until there’s a whole pizza with 8 slices. Refactor this program in two ways:

- Use a while loop.
- Use a do-while loop.

```kotlin
fun main() {
    var pizzaSlices = 0
    while (pizzaSlices < 7) {
        pizzaSlices++
        println("There's only $pizzaSlices slice/s of pizza :(")
    }
    pizzaSlices++
    println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza! :D")
}
```

```kotlin
Example solution 2
 {...}
fun main() {
    var pizzaSlices = 0
    pizzaSlices++
    do {
        println("There's only $pizzaSlices slice/s of pizza :(")
        pizzaSlices++
    } while (pizzaSlices < 8)
    println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza! :D")
}
```

Write a program that simulates the Fizz buzz game. Your task is to print numbers from 1 to 100 incrementally, replacing any number divisible by three with the word "fizz", and any number divisible by five with the word "buzz". Any number divisible by both 3 and 5 must be replaced with the word "fizzbuzz".

```kotlin
Example solution
 {...}
fun main() {
    for (number in 1..100) {
        println(
            when {
                number % 15 == 0 -> "fizzbuzz"
                number % 3 == 0 -> "fizz"
                number % 5 == 0 -> "buzz"
                else -> number.toString()
            }
        )
    }
}
```

You have a list of `words`. Use `for` and `if` to print only the words that start with the letter `l`.

```kotlin
fun main() {
    val words = listOf("dinosaur", "limousine", "magazine", "language")
	for (word in words) {
        if (word.startsWith("l")) {
            println(word)
        }
    }
}
```


---

#### Functions

Write a function called `circleArea` that takes the radius of a circle in `integer` format as a parameter and outputs the area of that circle.

```kotlin
import kotlin.math.PI

fun circleArea(radius: Int): Double {
    return PI * radius * radius
}
```

```kotlin
fun circleArea(radius: Int): Double = PI * radius * radius
```

You have a function that translates a time interval given in hours, minutes, and seconds into seconds. In most cases, you need to pass only one or two function parameters while the rest are equal to 0. Improve the function and the code that calls it by using default parameter values and named arguments so that the code is easier to read.

```kotlin
fun intervalInSeconds(hours: Int = 0, minutes: Int = 0, seconds: Int = 0) =
    ((hours * 60) + minutes) * 60 + seconds

fun main() {
    println(intervalInSeconds(1, 20, 15))
    println(intervalInSeconds(minutes = 1, seconds = 25))
    println(intervalInSeconds(hours = 2))
    println(intervalInSeconds(minutes = 10))
    println(intervalInSeconds(hours = 1, seconds = 1))
}
```


##### Lambdas

You have a list of actions supported by a web service, a common prefix for all requests, and an ID of a particular resource. To request an action title over the resource with ID: 5, you need to create the following URL: `https://example.com/book-info/5/title`. Use a lambda expression to create a list of URLs from the list of actions.

```kotlin
fun main() {
    val actions = listOf("title", "year", "author")
    val prefix = "https://example.com/book-info"
    val id = 5
    val urls = actions.map { action -> "$prefix/$id/$action" }
    println(urls)
}
```

Write a function that takes an `Int` value and an action (a function with type `() -> Unit`) which then repeats the action the given number of times. Then use this function to print `Hello` 5 times.

```kotlin
fun repeatN(n: Int, action: () -> Unit) {
	for (_n in 1..n) {
        action()
    }
}

fun main() {
	repeatN(5) { println("Hello") }
}
```


---

#### Classes

Define a data class `Employee` with two properties: one for a `name`, and another for a `salary`. Make sure that the property for salary is mutable, otherwise you won’t get a salary boost at the end of the year! The `main` function demonstrates how you can use this `data class`.

```kotlin
data class Employee(val name: String, var salary: Int)

fun main() {
    val emp = Employee("Mary", 20)
    println(emp)
    emp.salary += 10
    println(emp)
}
```

To test your code, you need a generator that can create random employees. Define a class with a fixed list of potential names (inside the class body), and that is configured by a minimum and maximum salary (inside the class header).

```kotlin
import kotlin.random.Random

data class Employee(val name: String, var salary: Int)

class RandomEmployeeGenerator(var minSalary: Int, var maxSalary: Int) {
    val names = listOf("John", "Mary", "Ann", "Paul", "Jack", "Alice")
    
    fun generateEmployee() = Employee(
        name = names.random(),
        salary = Random.nextInt(from = minSalary, until = maxSalary)
    )
}

fun main() {
    val empGen = RandomEmployeeGenerator(10, 30)
    println(empGen.generateEmployee())
    println(empGen.generateEmployee())
    println(empGen.generateEmployee())
    empGen.minSalary = 50
    empGen.maxSalary = 100
    println(empGen.generateEmployee())
}
```


---

#### Null-safety

You have the `employeeById` function that gives you access to a database of employees of a company. Unfortunately, this function returns a value of the `Employee?` type, so the result can be `null`. Your goal is to write a function that returns the `salary` of an employee when their `id` is provided, or `0` if the employee is missing from the database.

```kotlin
Example solution
 {...}
data class Employee (val name: String, var salary: Int)

fun employeeById(id: Int) = when(id) {
    1 -> Employee("Mary", 20)
    2 -> null
    3 -> Employee("John", 21)
    4 -> Employee("Ann", 23)
    else -> null
}

fun salaryById(id: Int) = employeeById(id)?.salary ?: 0

fun main() {
    println((1..5).sumOf { id -> salaryById(id) })
}
```
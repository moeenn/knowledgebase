#### Installation
Scala tools management software is called `coursier`. Visit their website to see latest installation instructions. After it has been installed and `bin` location has been added to `$PATH`, run the following command.

```bash
$ cs install scala3 metals bloop sbt sbtn coursier scalac scalafmt
```


---

#### Variables

```scala
val num: Int = 10
val floatNum: Double = 10.5
val bigNumber: BigInt = 1_000_000_000
val money: BigDecimal = 1_000_000_000_000.001
val character: Char = 'c'
val flag: Boolean = false
val name: String = "Admin"
```

```scala
// mutable variable
var mutableNumber: Int = 300

// type inference: String
val inferredTypeVariable = "hello world"
```

```scala
// string interpolation
val name = "User"
val message = s"Hello, $name"
```

```scala
// heterogeneous collection i.e. tuple
val multipleValues: (Int, Double, Char) = (10, 30.55, 'a')

// homogeneous collection i.e. array, list, vector
val numsArray: Array[Int] = Array(10, 20, 30, 40)
val numsList: List[Int] = List(10, 20, 30, 40)
val numsVector: Vector[Int] = Vector(10, 20, 30, 40)
```

```scala
val optionalInt: Option[Int] = Some(10)
val optionalDouble: Option[Double] = None
```

```scala
// Either is similar to Result<T, E> in rust
// Left conventionally means error, and right  means successful value
val result: Either[String, Int] = Right(30)
val anotherResult: Either[String, Boolean] = Left("Reason for some error")
```

```scala
import scala.util.{ Try, Failure, Success }

val result: Try[Int] = Success(300)
val resultFailed: Try[Int] = Failure(new Throwable("Some random exception"))
```


---

#### Lists

```scala
val nums = List(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

// map & filter
val timesTen = nums.map(_ * 10)
val even = nums.filter(_ % 2 == 0)

// map by calling object methods
val cities = List("Lahore", "Karachi", "Islamabad", "Faisalabad")
val upcased = cities.map(_.toUpperCase)

// reduce (i.e. sum all numbers)
val sumOne = nums.reduce((a, b) => a + b)
val sumTwo = nums.reduceRight(_ + _)

// generate range (end is non-inclusive)
val oneToTen = List.range(1, 11)
val oddOneToTen = List.range(start = 1, end = 11, step = 2)

// look-up value
val fiveValue: Option[Int] = nums.find(_ == 5)

// remove value which satify predicate
val greaterThanFive = nums.dropWhile(_ < 6)
```

```scala
@main def main: Unit =
  // List from range: start and end inclusive
  val numsList = (1 to 8).toList
  printIterable(numsList)
  
  val numsArray = (1 to 10).toArray
  printIterable(numsArray)

  val numsArrayWithStep = (0 to 100 by 10).toList
  printIterable(numsArrayWithStep)

def printIterable(list: Iterable[Int]) = list.foreach(println)
```

```scala
// list methods can also be called on Range.Inclusive type
val nums = (1 to 8).map(_ * 3).toList
```


---

#### Map (i.e. Hash-map)

```scala
var superHeros = Map(
  "Batman" -> "Bruce Wayne",
  "Iron man" -> "Tony Stark",
  "Deadpool" -> "Wade Wilson",
)

// add a new item
superHeros += ("Superman" -> "Clark Kent")

// lookup value
val result: Option[String] = superHeros.get("Batman")

// remove a value
superHeros = superHeros.removed("Deadpool")
```


---

#### Optional

```scala
val optionalNum: Option[Int] = Some(300)
optionalNum.isEmpty   // false
optionalNum.isDefined // true
```


---

#### Variable Evaluation

```scala
val num: Int = {
  println("this is a normal value")
  42
}

@main def main: Unit =
  println(num)
  println(num)

// Output:
// this is a normal value
// 42
// 42
```

```scala
// lazy values are only initialized on their first call
lazy val lazyNum: Int = {
  // this message will only be printed once at value initialization
  println("this is a lazy value")
  500
}

// functions declared without parenthesis, must be called without parenthesis
def numFunc: Int = {
  println("this is a returned value from function")
  700
}

@main def main: Unit =
  println(numFunc)
  println(lazyNum)
  println(lazyNum)

// Output:
// this is a returned value from function
// 700
// this is a lazy value
// 500
// 500
```


---

#### Functions

```scala
def simplePureFunc(): Int = 42

def pureFuncWithBodyAndImplicitReturns(name: Option[String]): String = 
  name match {
    case Some(n) => s"Hello, $n!"
    case None => "Hello there!"
  }

val simpleLambda = (n: Int) => n * 2 
```

```scala
def hgherOrderFunc(v: Iterable[Int], f: (Int) => Int): Iterable[Int] = v.map(f)

def hgherOrderGenericFunc[A, B](v: Iterable[A], f: (A) => B): Iterable[B] =   
  v.map(f)
```

```scala
def curriedFunc(a: Int)(b: Int): Int = a * b

@main def main: Unit =
  val resultOne: Int => Int = curriedFunc(10)
  val resultTwo: Int = resultOne(20)
  println(resultTwo)
```

```scala
def customMap[A, B](v: List[A], f: A => B): List[B] = 
  @annotation.tailrec
  def loop(rem: List[A], acc: List[B]): List[B] = rem match {
      case Nil => acc.reverse
      case head :: tail => loop(tail, f(head) :: acc)  
  }
     
  loop(v, Nil)

@main def main: Unit =
  val result = customMap((0 to 10).toList, _ * 10)
  println(result)
```


---

#### Case classes

```scala
import java.util.UUID

enum UserRole:
  case ADMIN, USER

case class Password(
  hash: String
)

case class User(
  id: String,
  email: String,
  password: Option[Password],
  role: UserRole,
)

def id(): String = UUID.randomUUID().toString()

@main def main(): Unit =
  val users: List[User] = List(
    User(
      id = id(),
      email = "admin@site.com",
      password = Some(Password("caskjcbaksjbck")),
      role = UserRole.ADMIN,
    ),
    User(
      id = id(),
      email = "user@site.com",
      password = None,
      role = UserRole.USER,
    )
  )

  val foundUser: Option[User] = users.find(u => u.email == "admin@site.com")
  val message = foundUser match {
    case Some(user) => s"Found user: ${user.email}"
    case None => "User not found"
  }

  println(message)
```


---

#### Packages and Imports

```
src/
	main/
		scala/
			Main.scala
			modules/
				user/
					User.scala
				password/
					Password.scala
				userRole/
					UserRole.scala
```

```scala
// File: Main.scala
package app

import app.modules.user.User
import app.modules.password.Password
import app.modules.userRole.UserRole

@main def main: Unit =
  val user = User (
    id = 300,
    email = "admin@site.com",
    password = Some(Password("123_Apple")),
    role = UserRole.Admin,
  )
  
  println(user)  
```

```scala
// File: User.scala
package app.modules.user

import app.modules.password.Password
import app.modules.userRole.UserRole

case class User(
  id: Int,
  email: String,
  password: Option[Password],
  role: UserRole,
)
```

```scala
// File: Password.scala
package app.modules.password

case class Password (
  hash: String
)
```

```scala
// File: UserRole.scala
package app.modules.userRole

enum UserRole:
  case Admin, Customer
```


---


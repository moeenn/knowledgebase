#### Installation
Scala tools management software is called `coursier`. Visit their website to see latest installation instructions. After it has been installed and `bin` location has been added to `$PATH`, run the following command.

```bash
$ cs install scala3 metals bloop sbt sbtn coursier ammonite scalac scalafmt
```


#### Starting a new Project

```bash
# for scala3
$ sbt new scala/scala3.g8

# for scala2
$ sbt new scala/hello-world.g8
```


---

#### Variables

```scala
val num: Int = 10
val money: Double = 10.5
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

#### Case classes

```scala
// enum definition
sealed trait UserRole
case object Admin extends UserRole
case object Employee extends UserRole
case object Customer extends UserRole

case class Password(hash: String)

case class User(
    id: Long,
    email: String,
    password: Password,
    role: UserRole
)

object Main extends App {
  val users: List[User] = List(
    User(
      id = 10,
      email = "admin@site.com",
      password = Password("dsalcnalkscnl"),
      role = Admin
    ),
    User(
      id = 20,
      email = "customer@site.com",
      password = Password("dsalcnalkscnl"),
      role = Customer
    ),
    User(
      id = 30,
      email = "employee@site.com",
      password = Password("dsalcnalkscnl"),
      role = Employee
    )
  )

  val user: Option[User] = users.find(user => user.id == 50)
  val message = user match {
    case Some(user) => s"Found: ${user.email}"
    case None => "User not found"
  }

  println(message)
}
```


---

#### Packages and Imports

```
src
	main
		scala
			app
				Main.scala
				modules
					user
						User.scala
					password
						Password.scala
					userRole
						UserRole.scala
```

```scala
// file: Main.scala
package app

import app.modules.password.Password
import app.modules.userRole._
import app.modules.user.User

object Main extends App {
  val user = User(
    id = 100,
    email =  "admin@site.com",
    password = Password("canklsclascnk"),
    role = Admin,
  )

  println(user)
}
```

```scala
// file: Password.scala
package app.modules.password

case class Password(hash: String)
```

```scala
// file: UserRole.scala
package app.modules.userRole

sealed trait UserRole
case object Admin extends UserRole
case object Customer extends UserRole
```

```scala
// file: User.scala
package app.modules.user

import app.modules.password.Password
import app.modules.userRole._

case class User(
  id: Long,
  email: String,
  password: Password,
  role: UserRole,
)
```


---

#### Functions and methods
Scala does not allow top level function declarations. All functions must be encased in objects or classes.

```scala
// file: app/acption/Action.scala
package app.action

object Action {
  def factorial(n: Int): BigInt = {
    if (n == 0) return 1
    return n * Action.factorial(n - 1)
  }

  def withSideEffects(): Unit = {
    println("performing action with side effects...")
  }

  def shorthandAdd(a: Int, b: Int): Int = a + b
}
```

```scala
// file: app/Main.scala
package app

import app.action.Action

object Main extends App {
  val result = Action.factorial(n = 50)
  println(result)

  // anonymous function
  val anon = () => println("performing some action")
  anon()
}
```

```scala
// returning error states from functions
object Database {
  def getUserCount(siteId: Long): Either[String, Long] = siteId match {
    case 20 => Left("Provided site has been disabled")
    case _ => Right(siteId * 10)
  }
}

object Main extends App {
  val dbResult = Database.getUserCount(40)
  val userMessage = dbResult match {
    case Left(msg) => s"error: ${msg}"
    case Right(value) => s"number of users: ${value}"
  }

  println(userMessage)
}
```


---

#### Futures

```scala
package app

import scala.concurrent.{ Future, Await }
import scala.concurrent.duration._
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.{ Failure, Success }
import java.time.Duration

case class Site(
  id: Long,
  name: String,
  initials: String, 
)

object Database {
  def findSiteById(siteId: Long): Future[Either[String, Site]] = Future {
    // simulate IO delayed operation
    Thread.sleep(1000)

    siteId match {
      case 10 => Left(s"Site not found: ${siteId}")
      case _ => Right(Site(id = siteId, name = "Site One", initials = "SO" ))
    }
  }
}

object Main extends App {
  // does not block thread, registers a callback when future completes
  Database.findSiteById(10).onComplete {
    case Failure(exception) => println("failed to get data")
    case Success(value) => value match {
      case Left(value) => println(s"success: ${value}")
      case Right(value) => println(s"error: ${value}")
    }
  }

  // blocks thread to get value out of Future
  val result = Await.result(Database.findSiteById(20), atMost = 2.seconds) match {
    case Left(value) => s"error: ${value}"
    case Right(value) => s"success: ${value}"
  }
  println(result)
}
```
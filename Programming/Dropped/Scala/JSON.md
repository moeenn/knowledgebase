We can use `uPickle` for working with `JSON`.


```
// SBT
"com.lihaoyi" %% "upickle" % "3.1.3" 

// Mill
ivy"com.lihaoyi::upickle:3.1.3" 
```


---

#### Usage

```scala
import upickle.default.{ ReadWriter, macroRW, write, read }

case class Password(hash: String)
object Password {
  implicit val rw: ReadWriter[Password] = macroRW
}

case class User(
  id: Long,
  email: String,
  password: Password
)
object User {
  implicit val rw: ReadWriter[User] = macroRW
}


object Action {
  def usersToJSON(users: List[User]): String = write(users)
  def parseUserJSON(json: String): User = read[User](json)
}

object Main extends App {
  val users: List[User] = List(
    User(id = 10, email = "admin@site.com", password = Password("1231231231")),
    User(id = 20, email = "customer@site.com", password = Password("asjaksjb")),
  )

  println(Action.usersToJSON(users))

  val rawJSON = """{ 
    "id": 300, 
    "email": "random@site.com",
    "password": {
      "hash": "acmcnlascj293183"
    }
  }"""

  println(Action.parseUserJSON(rawJSON))
}
```



---

#### Handling Parse Exceptions
In case of parse failure, `uPickle` with throw an Exception. We can handle as follows.

```scala
import scala.util.{ Try, Success, Failure }
...

object Action {
  def parseUserJSON(json: String): Either[String, User] = Try(read[User](json)) match {
    case Success(value) => Right(value)
    case Failure(exception) => Left(exception.getMessage())
  }
}

object Main extends App {
  // missing id key
  val rawJSON = """{ 
    "ids": 300, 
    "email": "random@site.com",
    "password": {
      "hash": "acmcnlascj293183"
    }
  }"""

  println(Action.parseUserJSON(rawJSON))
}
```
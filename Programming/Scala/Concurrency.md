
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


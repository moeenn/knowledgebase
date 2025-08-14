
#### Hello world

```scala
@main def main() =
  val message = greet("Admin")
  println(message)


def greet(name: String): String = s"Hello, $name!"
```

```bash
$ scala ./App.scala
```


---

#### Basic data types

```scala
val b: Byte = 1
val i: Int = 1
val l: Long = 1
val s: Short = 1
val d: Double = 2.0
val f: Float = 3.0
```

```scala
var a = BigInt(1_234_567_890_987_654_321L)
var b = BigDecimal(123_456.789)
```

```scala
val someValue: Option[Int] = Some(10)
val noValue: Option[Int] = None
```

```scala
val success: Either[String, Int] = Right(100) 
val failure: Either[String, Int] = Left("Error occurred")
```



---

#### Map

```scala
@main def main() =
	val capitals = Map(
		"Pakistan" -> "Islamabad",
		"China" -> "Beijing",
		"USA" -> "Washington"
	)

	// loop over all key values.
	for (country, capital) <- capitals do
		println(s"$country capital is $capital")
		
	// add new element or update existing key.
	val updatedMap = capitals + ("England" -> "London")
	println(updatedMap)


	val marvel = Map(
		"Iron man" -> "Tony Stark",
		"Captain America" -> "Steve Rogers"
	)
	
	val dc = Map(
		"Batman" -> "Bruce Wayne",
		"Superman" -> "Clark Kent"
	)

	// merge maps.	
	val superHeroes = marvel ++ dc
	println(superHeroes)
  
	// read value.
	val batmanName: Option[String] = superHeroes.get("Batman")
	println(batmanName) 
	
	// remove key.
	val heroesWithoutIronMan = superHeroes - "Iron man"
	println(heroesWithoutIronMan)
```


---

#### Try

```scala
import scala.util.{Try, Success, Failure}

def dubiousFunction(n: Int): Int = {
	if n == 10 then
		throw Exception("cannot process 10")		
	return n * 10
}

@main def main() = {
	val res = Try(dubiousFunction(10))
	val message = res match {
		case Success(v) => s"result: $v" 
		case Failure(f) => s"error: $f"
	}
		
	println(message)
}
```

```scala
@main def main() = {
	val successTry: Try[Int] = Try {
		10 + 20
	}
	
	val failedTry: Try[Int] = Try {
		throw new Exception("some random error here")
	}
}
```


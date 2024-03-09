```scala
// basic usage
val num = 6
val result = num match {
  case 1                => "One"
  case 2 | 4 | 6        => "Two / Four / Six"
  case 3                => "Three"
  case n if n % 10 == 0 => "Multiple of 10"
  case _                => "Unexpected number"
}
```

```scala
// deconstruction of case classes
case class Person(name: String, age: Int)

object Action {
  def greetUser(person: Person) = person match {
    case Person("Bob", _) => "Hello old friend!"
    case Person(_, 40) => "Welcom our distinguished person"
    case Person(name, _) => s"Welcome, ${name}!"
    // a default case can also appear here i.e. case _
  }
}
```

```scala
// list extractor patterns
val nums = List(1, 2, 3, 4, 5, 6, 7, 8)
val result = nums match {
  case List(_, _, 3, n, _*) => s"Third element is 3 and fourth is $n"
  case _                    => "List did not fit specified pattern"
}

// The `_*` variable argument (`vararg`) pattern, it means that the list can be // any size and we don't care.
```

```scala
// match list head or tail
val nums = List(1, 2, 3, 4, 5)
val result = nums match {
  case Nil       => "Provided list was empty"
  case 1 :: tail => s"List starts with one and ends with elements $tail"
  case _         => "List does not start with one"
}
```

```scala
// match variable length list starting and ending
val nums = List(1, 2, 3, 4, 5, 6, 7, 8)
val result = nums match {
  case List(1, _*) :+ 8 => "List starts with 1 and ends with 8"
  case _                => "List did not fit specified pattern"
}
```

```scala
// matching types
object Action {
  def getValue(): Any = 42
}

object Main extends App {
  // this mechanism is based on reflections, avoid to gain perf
  val result = Action.getValue() match {
    case _: Int    => "result was a valid number"
    case _: String => "result was a string"
    case _         => "we have something else"
  }

  println(result)
}
```
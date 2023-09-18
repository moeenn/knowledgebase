`mill` is an build tool for Java and Scala, and is a simpler alternative to `sbt`.


---

#### Installation

```bash
$ coursier install mill
```


---

#### Usage

```
build.sc
.gitignore
src/
	main/
		scala/
			Main.scala
out/
```

```gitignore
.bloop
.metals
.vscode
out
```

```scala
// file: build.sc
import mill._, scalalib._

object foo extends RootModule with ScalaModule {
  def scalaVersion = "2.13.11"

  // def ivyDeps = Agg(
  //   ivy"com.lihaoyi::scalatags:0.8.2",
  // )
}
```

```scala
// file: Main.scala
object Main extends App {
  println("hello world")
}
```


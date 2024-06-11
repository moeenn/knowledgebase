```bash
# add lsp support to the system
$ rustup component add rust-analyzer
```


---

#### Getting started
```rust
/* file: main.rs */  
fn main() {  
    println!("Hello Computer");  
}
```

```bash
# compile directly  
$ rustc main.rs  
  
# compile using cargo (recommended)  
$ cargo build

# quickly execute
$ cargo -q run
```

---

##### Statements vs. Expressions
-   Statements perform an action but don’t return a value
-   Expressions return a value


---

####  Printing to console
```rust
println!("Hello {}, your order is ready.", name);  
println!("Hello {name}, your order is ready.");

/* debug trait */
/* print out complex data-structures */  
println!("{:?}", (1, true, "Sample"));  
  
/* print formatted output */  
println!("{:#?}", (1, true, "Sample"));
```

---

#### Variables and constants
```rust
/* immutable */  
let action = "Conquer Earth";  
  
/* mutable */  
let mut place = "Pacific";
```

```rust
/**  
*  variable name must be uppercase and a type should be defined  
*  rust doesn't allow global mutable state which is why all global  
*  variables must be const  
*/  
const MAX_THREADS: u8 = 200;  
  
fn main() {  
    println!("Max threads: {MAX_THREADS}");  
}
```

---

#### Primitive (scalar) data types
|       Description | Type                             |
| ----------------: | :------------------------------- |
| Unsigned integers | `u8, u16, u32, u64, u128`        |
|   Signed integers | `i8, i16, i32, i64, i128`        |
|            Floats | `f32, f64`                       |
|           Boolean | `true, false`                    |
|         Character | `char (used with single-quotes)` |

##### Compound types
| Description | Type                                                   |
| ----------: | :----------------------------------------------------- |
|       Array | `Fixed-sized collection of one data type`              |
|       Tuple | `Fixed-sized array of related data of different types` |

##### Get variable type
```rust
fn type_of<T>(_: &T) -> String {  
    format!("{}", std::any::type_name::<T>())  
}
```


---

#### Control-flow
```rust
let age: u8 = 19;  
let has_id: bool = false;  
  
if age >= 18 && has_id {  
    println!("You are old enough and allowed to vote!");  
} else if age < 18 || has_id {  
    println!("You are not not allowed to vote ...");  
} else {  
    println!("You don't have the ID and you cannot vote");  
}
```

```rust
let is_hot = true;  
let is_girl = true;  

/* rust does not have ternary operator */
let allow_entry = if is_girl && is_hot { true } else { false };  
println!("The Bartender will allow entry? {allow_entry}");
```

**Note** 
-   Any statement inside a block is considered a return value if no semicolon is present at the end of the line
-   The above syntax is just ordinary if-else condition which is following the semicolon rule

---

#### Loops
```rust
use std::{thread, time};

fn main() {
    let second = time::Duration::from_secs(1);

    /* infinitely loop every 1 second */
    loop {
        println!("looping through");
        thread::sleep(second);
    }
}
```

```rust
for count in 0..100 {  
    if count % 15 == 0 {  
        println!("{count} Fizzbuzz");  
        continue;  
    }  
  
    if count % 3 == 0 {  
        println!("{count} Fizz");  
        continue;  
    }  
  
    if count % 5 == 0 {  
        println!("{count} Buzz");  
        continue;  
    }  
  
    println!("{count}")  
}
```


---

#### Match statement
```rust
fn main() {  
  let num = 3;  
  
  let wording = match num {  
    1 => "One",  
    2 => "Two",  
    3 => "Three",  
    _ => "Other numbers...",  
  };  
  
  println!("{wording}");  
}
```

```rust
fn main() {  
    let num = 18;  
   
    let msg = match num {  
      0 => "Zero",  
      1 | 3 | 5 | 7 | 9 => "Odd",  
      2 | 4 | 6 | 8 | 10 => "Even",  
      11..=20 => "In range 11-20 inclusive",  
      _ => "Other numbers...",  
    };  
  
    println!("{msg}")  
}
```

---

#### Functions
```rust
fn main() {  
  log("This is an example log message", 2);  
  println!("Is Even?\t{}", is_even(20));  
  
  let total = sum(30.5, 40.3, 50.2);  
  println!("Sum:\t{}", total);  
}  
  
/* no returned values */  
fn log(msg: &str, level: u8) {  
  println!("Level {level}:\t{msg}");  
}  
  
/* returned values */  
fn is_even(num: i32) -> bool {  
  /* no semicolon means returned value */  
  num % 2 == 0  
}  
  
fn sum(a: f64, b:f64, c: f64) -> f64 {  
  a + b + c  
}
```

##### Optional function returns
```rust
fn main() {  
  let result = match div(200, 0) {  
      Some(n) => n,  
      None => 0,  
  };  
  
  println!("{}", result);  
}  
  
fn div(a: u16, b: u16) -> Option<u16> {  
  return if b == 0 { None } else { Some(a / b) };  
}
```

##### Multiple returns from a function
Tuples can be returned from functions with multiple values. Although this is allowed, prefer returning structs from functions.

```rust
fn main() {  
    let (value, error) = action();  
    println!("{:?}", (value, error));  
}  
  
fn action() -> (i32, bool) {  
    (300, false)  
}
```

##### Closures
```rust
let c: i32 = 100;  
let add = |n1: i32, n2: i32| n1 + n2 + c;

println!("Total:\t{}", add(10, 20));
```

```rust
/* type definitions are optional */
let add = |n1, n2| n1 + n2 + c;
```

---

#### Struct
```rust
use std::fmt;

struct Color {  
	red: u8,  
	green: u8,  
	blue: u8,  
} 

impl Color {
	fn new(r: u8, g: u8, b: u8) -> Self {
		Color {
			red: r,
			green: g,
			blue: b,
		}
	}
}

impl fmt::Display for Color {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({}, {}, {})", self.red, self.green, self.blue)
	}
}

fn main() {
	let white = Color::new(255, 255, 255);
	println!("{}", white);
}
```

```rust
#[derive(Debug)]
struct User {
    username: String,
    email: String,
    signin_count: u64,
    active: bool,
}

fn build_user(username: String, email: String) -> User {
    User {
        username,
        email,
        signin_count: 0,
        active: true,
    }
}

fn main() {
    let user = User {
        email: String::from("sample@site.com"),
        username: String::from("sample"),
        signin_count: 0,
        active: true,
    };

    let user_two = build_user(String::from("admin"), String::from("admin@site.com"));

    let user_three = User {
        active: false,
        signin_count: 10,
        ..user_two
    };

    println!("{:?}", user);
    println!("{:?}", user_three);
}
```

##### Tuple structs
```rust
struct Color(u8, u8, u8);  
  
fn main() {  
  let mut c = Color(255, 0, 0);  
  c.1 = 100;  
  
  println!("Color: {}:{}:{}", c.0, c.1, c.2);  
}
```

##### Generic struct
```rust
struct Details<T, E> {  
  start: T,  
  end: E  
}  
  
fn main() {  
  /* rust can automatically infer the data types */  
  let data_nums = Details {  
    start: 20,  
    end: "Message associated with the generic struct"  
  };  
  
  println!("{:?}", (data_nums.start, data_nums.end));  
}
```

```rust
/* types can also be specified using turbofish syntax */
let data_nums = Details::<u32, u16>{  
  start: 20,  
  end: 50  
};
```

##### Struct methods
```rust
#[derive(Debug)]  
struct Rectangle {  
  height: u64,  
  width: u64,  
}  
  
impl Rectangle {  
  fn new(height: u64, width: u64) -> Rectangle {  
    Rectangle{height, width}  
  }  
  
  /* getter */  
  fn area(&self) -> u64 {  
    self.height * self.width  
  }  
  
  /* setter */  
  fn set_width(&mut self, w: u64) {  
    self.width = w;  
  }  
  
  fn is_larger(&self, other: &Rectangle) -> bool {  
    self.area() > other.area()  
  }  
}  
  
#[test]  
fn test_area() {  
  let rect = Rectangle{ height: 300, width: 200};  
  let expected = 60_000;  
  let got = rect.area();  
   
  assert_eq!(expected, got);  
}  
  
#[test]  
fn test_is_larger() {  
  let rect = Rectangle{ height: 10, width: 20};  
  let rect_two = Rectangle::new(5, 8);  
   
  assert_eq!(true, rect.is_larger(&rect_two));  
}  
  
fn main() {  
  let mut rect = Rectangle::new(10, 20);  
  rect.set_width(25);  
  println!("{:?} - {}", rect, rect.area());  
}
```

##### Printing custom structs
In the above example we used the `derive(Debug)` to print out the entire struct to console. Alternatively, we can implement `fmt::Display` trait on our custom struct to achieve the same result.

```rust
use std::fmt;

struct Entity {
  x: u16,
  y: u16,
}

impl Entity {
    fn new() -> Entity {
        Entity { x: 0, y: 0 }
    }
}

impl fmt::Display for Entity {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Entity(x={}, y={})", self.x, self.y)
    }
}
```

---

#### Enums
Every `enum` value is a `struct`. These values can be unit values (i.e. empty)

```rust
/* enum and variants */  
enum Directions { Up, Down, Left, Right }  
  
/* enum as argument */  
fn move_entity(d: Directions) {  
  let msg = match d {  
    Directions::Up => "Moving Up",  
    Directions::Down => "Moving Down",  
    Directions::Left => "Moving Left",  
    Directions::Right => "Moving Right"  
  };  
  
  println!("{msg}");  
}  
  
fn main() {  
  move_entity(Directions::Up);  
  move_entity(Directions::Left);  
  move_entity(Directions::Down);  
  move_entity(Directions::Right);  
}
```

```rust
#[derive(Debug)]  
enum IPKind {  
  V4,  
  V6,  
}  
  
#[derive(Debug)]  
struct IP {  
  kind: IPKind,  
  address: String,  
}  
  
fn main() {  
  let localhost = IP {  
    kind: IPKind::V4,  
    address: String::from("127.0.0.1"),  
  };  
  
  println!("{:?}", localhost);  
}
```

```rust
#[derive(Debug)]  
enum IP {  
  V4(u8, u8, u8, u8),  
  V6(String),  
}  
  
impl IP {  
  fn new_v4() -> IP {  
    IP::V4(0, 0, 0, 0)  
  }  
  
  fn home() -> IP {  
    IP::V4(127, 0, 0, 1)  
  }  
}  
  
fn main() {  
  let home = IP::home();  
  println!("{:?}", home);  
}
```

##### Printing `enum` values
```rust
use std::fmt;

enum LogLevel {
    INFO,
    WARN,
    ERROR,
}

impl fmt::Display for LogLevel {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            LogLevel::INFO => write!(f, "info"),
            LogLevel::WARN => write!(f, "warn"),
            LogLevel::ERROR => write!(f, "error"),
        }
    }
}

fn log(level: LogLevel, message: &str) {
    println!("{level}: {message}");
}

fn main() {
    log(LogLevel::INFO, "Hello world");
}
```

##### Option `enum`
```rust
enum Option<T> {
  Some(T),
  None,
}
```

**Note:** `Some` have a value of `T` and `None` is a unit value.

##### Handling optional data
```rust
struct User {
  id: u32,
  name: String,
}

struct UserStore {
  users: Vec<User>
}

impl UserStore {
  fn new(users: Vec<User>) -> UserStore {
    return UserStore { users: users }
  }

  fn find_by_id(self, id: u32) -> Option<User> {
    for user in self.users {
      if user.id == id {
        return Some(user);
      }
    }

    None
  }  
}

fn main() {
  let users = vec![
    User{id: 1, name: String::from("user")},
    User{ id: 2, name: String::from("admin")},
  ];   

  let user_store = UserStore::new(users);
  let result = match user_store.find_by_id(4) {
    Some(user) => format!("User(id={}, name={})", user.id, user.name),
    None => String::from("user not found"),
  };

  println!("{result}")
}
```

**Note:** When we write `None` it actually means `Option::None`.

---

#### Guesssing game

```rust
use std::io;
use rand::{Rng};
use std::cmp::Ordering;
use colored::*;

fn main() {
  let secret = rand::thread_rng().gen_range(0..101);
  println!("Random number: {}", secret);

  loop {
    let mut guess = String::new();

    println!("Please enter a number: ");
    io::stdin()
      .read_line(&mut guess)
      .expect("Failed to read input");

    let guess: u32 = match guess.trim().parse() {
      Ok(num) => num,
      Err(err) => {
        println!("{}", err);
        continue;
      },
    };

    match guess.cmp(&secret) {
      Ordering::Less => println!("{}", "Too small".red()),
      Ordering::Greater => println!("{}", "Too larger".red()),
      Ordering::Equal => {
        println!("{}", "You win".green());
        break;
      },
    };
  }
}
```

```toml
[dependencies]
rand = "0.8.4"
colored = "2.0.0"
```

---

#### Traits
Traits are like a combination of Interfaces and Abstract classes. 

```rust
trait Summary {
    fn summarize(&self) -> String; 
}

struct Article {
    author: String,
    headline: String,
    content: String,
}

impl Summary for Article {
    fn summarize(&self) -> String {
        format!("{} by {}", self.headline, self.author)
    }
}

struct Tweet {
    username: String,
    content: String,
    reply: bool,
    retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}


fn main() {
    let article = Article {
        author: String::from("Isaac Asimov"),
        headline: String::from("Foundation"),
        content: String::from("some random content..."),
    };

    println!("{}", article.summarize());

    let tweet = Tweet {
        username: String::from("elon.musk"),
        content: String::from("Dogecoin is memecoin..."),
        reply: false,
        retweet: false,
    };

    println!("{}", tweet.summarize());
}
```

##### Default trait method implementation
In the above example, we have only defined a function signature in the trait, we can also provide function default implementation in the trait. Any struct that implements this trait can override the default implementation.

```rust
struct Article {...}

impl Summary for Article {
    fn summarize_author(&self) -> String {
        format!("By: {}", self.author)
    }
}

struct Tweet {...}

impl Summary for Tweet {
    fn summarize_author(&self) -> String {
        format!("@{}", self.username)
    }

    /* overwrite default implementation */
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

trait Summary {
    fn summarize_author(&self) -> String;

    /* default implementation */
    fn summarize(&self) -> String {
        String::from("Read more...")
    }
}

fn main() {
    let article = Article {
        author: String::from("Isaac Asimov"),
        headline: String::from("Foundation"),
        content: String::from("some random content..."),
    };

    println!("{}\n{}", article.summarize(), article.summarize_author());

    let tweet = Tweet {
        username: String::from("elon.musk"),
        content: String::from("Dogecoin is memecoin..."),
        reply: false,
        retweet: false,
    };

    println!("\n\n{}\n{}", tweet.summarize(), tweet.summarize_author());
}
```

##### Traits as function arguments
The following function will accept any struct that implements the Summary trait. 

```rust
fn notify<T: Summary>(item: &T) {
    println!("Breaking news: {}", item.summarize());
}
```

Or more concisely as follows 

```rust
fn notify(item: &impl Summary) {
    println!("Breaking news: {}", item.summarize());
}
```

##### Traits as returned values

```rust
fn create_summarizable() -> impl Summary {
    Article {
        author: String::from("Isaac Asimov"),
        headline: String::from("Foundation"),
        content: String::from("some random content..."),
    }
}

fn main() {
    println!("{}", create_summarizable().summarize());
}
```

---

#### Generics

```rust
fn main() {
    let numbers = vec![20, 30, 50, 10, 5];
    println!("largest: {}", find_largest(numbers));

    let chars = vec!['a', 'f', 'x'];
    println!("largest: {}", find_largest(chars));
}

fn find_largest<T: PartialOrd + Copy>(numbers: Vec<T>) -> T {
    let mut largest = numbers[0];

    for &num in numbers.iter().skip(1) {
        if num > largest {
            largest = num;
        }
    }

    largest
}
```

**Note:**  `<T: PartialOrd + Copy>` refers to traits that are required to be implemented by the generic type.

##### Generic definition with `where`

```rust
fn notify<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {
    //
}
```

The above can be make more readable as follows

```rust
fn notify<T, U>(item_a: &T, item_b: &U) -> i32 
    where T: Display + Clone,
          U: Clone + Debug
{
    //
}
```

---

#### Generic lifetime annotation (Lifetimes)
Lifetimes provide information to the borrow-checker about how long a reference will live.

```rust
fn main() {
    let str1 = String::from("abcd");
    let str2 = String::from("xyz");

    println!("Longest: {}", longest(str1.as_str(), str2.as_str()));
}

fn longest<'x>(a: &'x str, b: &'x str) -> &'x str {
    if a.len() > b.len() {
        a
    } else {
        b
    }
}
```

Explanation
- There is a relationship between the lifetimes of `a`, `b` and  the returned value; the lifetime of the returned reference will be the same as the smallest lifetime of the function arguments.

- Lifetime annotations don't change the lifetime, **they only provide additional information about the lifetimes of references to the borrow-checker**.


##### Another example
```rust
fn main() {
    let str1 = String::from("abcd");
    let result: &str;

    {
        let str2 = String::from("xyz");
        result = longest(str1.as_str(), str2.as_str());
    }

    println!("Longest: {}", result);
}

fn longest<'x>(a: &'x str, _b: &str) -> &'x str {
    a
}
```

Explanation
- Lifetime of `str1` is till the end of main

- Lifetime of `result` will be equal to the lifetime of `str1` because the returned reference from `longest` will always be equal to the lifetime of the argument a (notice there is no lifetime annotation for `b`).  


##### Specifying lifetime annotations
```rust
&i32            /* reference */
&'a i32         /* reference with explicit lifetime */
&'i32 mut i32   /* mutable reference with explicit lifetime */
```

##### Usage with structs
```rust
use std::fmt;

struct Entity<'a> {
    email: &'a str,
    dob: u8,
}

impl<'a> Entity<'a> {
    fn new(email: &'a str, dob: u8) -> Entity {
        Entity { email, dob }
    }
}

impl<'a> fmt::Display for Entity<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Entity(email={}, dob={})", self.email, self.dob)
    }
}

fn main() {
    let e = Entity::new("admin@site.com", 30);
    println!("{}", e);
}
```

---

#### Command Line Arguments
```rust
let args: Vec<String> = std::env::args().collect();
println!("Args: {:?}", args);
```

```rust
use std::env;

fn main() {
  let args = env::args();

  for arg in args.skip(1) {
      println!("{}", arg);
  }
}
```

`std::end::args()` returns an `iterator`. This syntax of the For-loop can be used with iterators. `skip()` tells the iterator to omit one value, which in this case is the first value i.e. name of the program executable.

**Note:** All Command line arguments are read as `String`. These arguments will need to be converted to numbers or boolean where necessary.

---

#### Convert types

##### Convert `u8` to `i32`
```rust
let a: u8 = 20;
let b = i32::from(a);

// alternatively
let c: i32 = a.into();

println!("{:?}", (a, b, c));
```

##### Convert string to other types
```rust
use std::process;
use std::str::FromStr;

/* return type of a variable as String */
fn type_of<T>(_: &T) -> String {
    format!("{}", std::any::type_name::<T>())
}

/* concrete: convert a str to i32 */
fn str_to_i32(input: &str) -> i32 {
    let num: i32 = match FromStr::from_str(input) {
        Ok(n) => n,
        Err(err) => {
            eprintln!("[error] {}", err);
            process::exit(1);
        }
    };

    num
}

/* generic: convert str to any type that implement FromStr trait */
fn str_to_type<T: std::str::FromStr>(input: &str) -> Option<T> {
    match FromStr::from_str(input) {
        Ok(n) => Some(n),
        Err(_) => None,
    }
}

fn main() {
    let num_str = "30";
    let num = str_to_i32(num_str);
    println!("num: {}, type: {}", num, type_of(&num));

    let bool_str = "false";
    let boolean = match str_to_type::<bool>(bool_str) {
        Some(b) => b,
        None => {
            eprintln!("error: failed to parse as boolean");
            process::exit(1);
        }
    };

    println!("boolean: {}, type: {}", boolean, type_of(&boolean));
}
```


---

#### Exit program

```rust
use std::process;

fn stop_program(n: i32) {
    if n == 30 {
        eprintln!("[error] exiting program");
        process::exit(1);
    }
}

fn main() {
    stop_program(30);
}
```


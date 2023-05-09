#### Ownership and borrowing

Ownership Rules
- Each value has a variable that is called its Owner
- There can only be one owner at a time 
- When the owner goes out of scope, the value will be dropped (deallocated)


#### Moving a value (i.e. taking ownership)
```rust
let msg1 = String::from("Message");
let msg2 = msg1;

println!("{}", msg1);
```

The above code will not compile because we are accessing a value (String “Message”) after it has been moved from owner `msg1` to `msg2`.

If we actually need to create a copy of the String, we can do the following. In this case the value will not be moved.

```rust
let msg_one = String::from("Message");
let msg_two = msg_one.clone();

println!("{}, {}", msg_one, msg_two);
```

Similarly, when we pass values to functions, they take ownership of the value (i.e. value is moved). The following code will not compile.

```rust
fn main() {
  let msg = String::from("Message");
  /* value is moved here */
  prints_value(msg);

  /* Error */
  println!("{}", msg);
}

fn prints_value(value: String) {
  println!("{}", value);
}
```

Conversely, a function can also give ownership of a value to another variable.

```rust
fn main() {
  let msg = gives_ownership();
  println!("{}", msg);
}

fn gives_ownership() -> String {
  String::from("Message")
}
```


#### Borrowing a value (without taking ownership)
```rust
fn main() {
  let msg = String::from("Message");
  let length = calc_length(&msg);

  println!("{}, {}", msg, length);
}

fn calc_length(value: &String) -> usize {
  value.len()
}
```

**Note**: We are not allowed to return dangling references from functions. The following code will **not compile**.

```rust
fn main() {
  let value = dangle_ref();
  println!("{}", value);
}

fn dangle_ref() -> &String {
  let value = String::from("Message");

  /* returning a dangling reference */
  &value
}
```


#### Modifying a borrowed value
```rust
fn main() {
  let mut value = String::from("Message");
  update_value(&mut value);

  println!("{}", value);
}

fn update_value(value: &mut String) {
  value.push('!');
}
```


#### Pointers
```rust
fn main() {
  let mut value = 30i32;
  update_value(&mut value, 50);
  println!("Value: {}", value);
}

fn update_value(value: &mut i32, new_value: i32) {
  *value = new_value;
}
```


#### Slices
Slices are used to reference a contiguous sequence of elements within a collection without taking their ownership. 

```rust
let arr = [1,2,3,4,5];
let slice = &arr[2..4];

for i in slice.iter() {
    print!("{} ", i);
}

// 3 4
```

**Note**: The end-index in range is non-inclusive. If we want the end-index to be included, we have to define the range as `2..=4`

If we are starting from the first element then we can omit the start of range. If we are going to the last element then we can omit the ending of range.

```rust
let msg = String::from("Hello world");
let first = &msg[..5];
let second = &msg[6..];
let copy = &msg[..];
```

```rust
fn main() {
  let msg = String::from("Hello world");
  let first = first_word(&msg);
  println!("{}", first);
}

fn first_word(value: &String) -> &str {
  let bytes = value.as_bytes();

  for (i, &item) in bytes.iter().enumerate() {
    if item == b' ' {
      return &value[..i];
    }
  }

  &value[..]
}
```

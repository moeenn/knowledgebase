#### Strings
There are two types of strings in Rust.
- `&str`: String literal, fixed length, immutable. Also called a slice of chars
- `String`: Heap allocated, variable length, mutable.

**Note**: A string literal i.e. `&str` is stored directly in the binary which is why it is immutable.


##### String functions
```rust
/* initializing a string */
let mut msg = String::from("This is a message");

/* find length */
let length = msg.len();
assert!(length == 17);

/* add one character to end */
msg.push('.');
assert!(msg.len() == 18);

/* add string to end */
msg.push_str(" Additional Message.");
assert!(msg.ends_with("Message."));

/* check if empty */
let is_empty = msg.is_empty();
assert!(!is_empty);

/* search substring inside string (bool) */
let contains = msg.contains("Additional");
assert!(contains);

/* replace. The original string is not changed. New string is returned */
let new_msg = msg.replace("Additional", "Some Other");
assert!(!new_msg.contains("Additional"));

/* loop through string words */
for word in "Hello Someone".split_whitespace() {
    println!("{word}");
}

/* convert string slice to string struct */
let str_slice: &str = "Hello";
let str_struct: String = str_slice.to_string();

/* string Concatenation */
let s_one = String::from("Hello ");
let s_two = String::from("World");  

let combined: String = s_one + &s_two;
assert!(combined.eq("Hello World"));

let combined = format!("{} {}", String::from("ABC"), "123");
assert!(combined.eq("ABC 123"));
```

---

#### Arrays
Arrays are Fixed Length containing only one type of data. Arrays are created on the Stack.

```rust
/* declare array, the type can be omitted */
let mut nums: [i8; 5] = [1, 2, 3, 4, 5];

/* update value in mutable array: NOT RECOMMENDED */
nums[1] = 10;

/* get single value - NOT RECOMMENDED */
let value_one = nums[0];

/* get single value - RECOMMENDED */
let value_two = nums.get(2).unwrap_or(&-1);

/* get array length */
let length = nums.len();
assert!(length == 5);

/* loop through array values */
for n in nums {
    println!("value: {n}");
}

println!("value_one: {value_one}, value_two: {value_two}");
println!("nums: {nums:?}, length: {length}");
```


##### Map
```rust
let nums = [1, 2, 3, 4, 5];

/// we cannot iterate over a vector directly, iter() returns an iterator
/// map() is a method on iterator which also returns an iterator
let results = nums.iter().map(|n| n * 2);

for result in results {
    println!("{}", result);
}
```


##### Filter
```rust
let nums = [1, 2, 3, 4, 5];
let results = nums.iter().filter(|&n| n % 2 == 0);
```


---

#### Tuples
```rust
/* declare type explicitly */
let origin_point: (u16, u16) = (0, 0);

/* let compiler infer type */
let point = (10, 20);

/* tuple unpacking */
let (x, y) = point;

/* access tuple value by index */
let origin_x = origin_point.0;
```

**Note**: An empty `tuple` is called a Unit Value. Any function that doesn’t return anything returns an empty tuple.

---

#### Vectors
```rust
let v: Vec<i8> = vec![10, 20, 30, 40, 50];
assert!(v.len() == 5);

/* this will build, but panic at runtime, therefore NOT RECOMMENDED */
let tenth = &v[10];
println!("{}", tenth);

/* recommended: get() returns Option<&i8> */
let third = match v.get(2).unwrap_or(&0);
assert!(second == &30);

/* add element to end of mutable vector */
v.push(60);
assert!(v.len() == 6);

/* pop last value */
let last: Option<i8> = v.pop();
assert!(last.unwrap_or(0) == 60);

/* loop through content of the vector */
for n in v {
  println!("{n}");
}
```

##### Note on vectors
Vectors are heap-allocated and dynamic-sized. Vectors utilize buffers for storing values. If a vector has a buffer of size 10, it can store up to 10 values. When the buffer is full and we push additional elements in the vector, the following actions occur

- A new buffer is created in heap memory twice the size of the previous buffer
- All elements from old buffer are copied to the new buffer 
- The old buffer is deallocated.

To optimize performance, we can initialize new vectors with a buffer size of our choosing. Our provided buffer size is only the starting size of the buffer and we still still be able to push elements into the vector once the buffer is full.

```rust
let v: Vec<i32> = Vec::with_capacity(100);
println!("nums: {:?} capacity: {}", v, v.capacity());
```

---

#### Hashmaps

```rust
use std::collections::HashMap;

fn main() {
  let mut scores: HashMap<u32, u8> = HashMap::from([
    (201, 30),
    (202, 50),
    (203, 20)
  ]);

  scores.insert(204, 70);
  assert!(scores.get(&204).unwrap_or(&0) == &70);

  /* loop through all items in the hashmap */
  for (k, v) in scores.iter() {
    println!("{k} - {v}");
  }

  /* perform action if index is found */
  if let Some(n) = scores.get(&203) {
    println!("Found: 203 - {n}");
  }
}
```

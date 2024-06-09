```rust
enum Option<T> {
  Some(T),
  None
}

enum Result<T, E> {
  Ok(T),
  Err(E)
}
```

##### Initial program
```rust
fn to_int(num: &str) -> i32 {
  // parse will infer data type from the return type in function signature 
  // if the program fails to parse a string as a i32, program will panic with default message
  // always avoid Result::unwrap in production code because it is untestable
  num.parse().unwrap()
}

fn sum_str_vec(nums: Vec<String>) -> String {
  let mut accum = 0i32;
  for num in nums {
    accum += to_int(&num);
  }

  accum.to_string()
}

#[test] 
fn test_sum_str_vec() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("30")];
  let sum = sum_str_vec(nums);

  assert!(sum == "60");  

  // cannot test panic
}
```


##### Panic with custom message
```rust
fn to_int(num: &str) -> i32 {
  // if string cannot be parsed as i32, panic with our custom message
  num.parse().expect("failed to parse as number")
}
```


##### Provide fallback value in case of parse error
```rust
fn to_int(num: &str) -> i32 {
  match num.parse() {
    Ok(n) => n,
    Err(_) => 0,
  }
}
```

The above code can be written more succinctly as follows.

```rust
fn to_int(num: &str) -> i32 {
  // if string cannot be parsed as number, 0 is used as fallback value
  num.parse().unwrap_or(0)
}

fn sum_str_vec(nums: Vec<String>) -> String {
 // 
}

#[test] 
fn test_sum_str_vec() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("30")];
  let sum = sum_str_vec(nums);
  assert!(sum == "60"); 

  // use shadowing to re-declare variables
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);
  assert!(sum == "30")
}
```


##### Allow caller to decide what to do with errors
```rust
fn to_int(num: &str) -> Option<i32> {
  match num.parse() {
    Ok(n) => Some(n),
    Err(_) => None
  }
}
```

The above code can be written more succinctly as follows.

```rust
fn to_int(num: &str) -> Option<i32> {
  // quickly convert Result to Option (error message is lost)
  num.parse().ok()
}
```

The above functions can be consumed as follows

```rust
fn sum_str_vec(nums: Vec<String>) -> String {
  let mut accum = 0i32;
  for num in nums {
    accum += match to_int(&num) {
      Some(n) => n,
      None => 0,
    }
  }

  accum.to_string()
}
```

**Note:** The test for this function will remain unchanged.


##### Only perform sum addition if Option has Some value 
```rust
fn sum_str_vec(nums: Vec<String>) -> String {
  let mut accum = 0i32;
  for num in nums {
    // extract n from Option::Some(n)
    if let Some(n) = to_int(&num) {
      accum += n;
    }
  }

  accum.to_string()
}
```


##### Fallback value for Option
```rust
fn sum_str_vec(nums: Vec<String>) -> String {
  let mut accum = 0i32;
  for num in nums {
    // provide fallback value for Option
    accum += to_int(&num).unwrap_or(0);
  }

  accum.to_string()
}
```


##### Propagate Optional values up the stack
```rust
fn sum_str_vec(nums: Vec<String>) -> Option<String> {
  let mut accum = 0i32;
  for num in nums {
    accum += match to_int(&num) {
      Some(n) => n,
      None => {
        return None;
      },
    }
  }

  Some(accum.to_string())
}
```

The above can be written more succinctly as follows.

```rust
fn sum_str_vec(nums: Vec<String>) -> Option<String> {
  let mut accum = 0i32;
  for num in nums {
    // propagate Option::None up the stack
    accum += to_int(&num)?
  }

  Some(accum.to_string())
}
```

```rust
#[test] 
fn test_sum_str_vec() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("30")];
  let sum = sum_str_vec(nums);

  assert!(!sum.is_none());
  if let Some(n) = sum {
    assert!(n == "60"); 
  }

  // use shadowing to re-declare variables
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);
  assert!(sum.is_none());
}
```

---

##### Convert Option to Result

```rust
struct SumError;

fn main() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);

  match sum {
    Ok(sum) => println!("sum: {sum}"),
    Err(_) => println!("error: failed to sum"),
  }
}

fn to_int(num: &str) -> Option<i32> {
  num.parse().ok()
}

fn sum_str_vec(nums: Vec<String>) -> Result<String, SumError> {
  let mut accum = 0i32;
  for num in nums {
    accum += match to_int(&num) {
      Some(n) => n,
      None => {
        return Err(SumError);
      }
    }
  }

  Ok(accum.to_string())
}

#[test] 
fn test_sum_str_vec() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("30")];
  let sum = sum_str_vec(nums);

  assert!(sum.is_ok());
  if let Ok(n) = sum {
    assert!(n == "60"); 
  }

  // use shadowing to re-declare variables
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);
  assert!(!sum.is_ok());
}
```

Function `sum_str_vec` can be written more precisely as follows. 

```rust
fn sum_str_vec(nums: Vec<String>) -> Result<String, SumError> {
  let mut accum = 0i32;
  for num in nums {
    accum += to_int(&num).ok_or(SumError)?;
  }

  Ok(accum.to_string())
}
```


##### Propagate Result up the stack
```rust
use std::num::ParseIntError;

fn main() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);

  match sum {
    Ok(sum) => println!("sum: {sum}"),
    Err(_) => println!("error: failed to sum"),
  }
}

fn to_int(num: &str) -> Result<i32, ParseIntError> {
  num.parse()
}

fn sum_str_vec(nums: Vec<String>) -> Result<String, ParseIntError> {
  let mut accum = 0i32;
  for num in nums {
    accum += to_int(&num)?;
  }

  Ok(accum.to_string())
}

#[test] 
fn test_sum_str_vec() {
  let nums = vec![ String::from("10"), String::from("20"), String::from("30")];
  let sum = sum_str_vec(nums);

  assert!(sum.is_ok());
  if let Ok(n) = sum {
    assert!(n == "60"); 
  }

  // use shadowing to re-declare variables
  let nums = vec![ String::from("10"), String::from("20"), String::from("abc")];
  let sum = sum_str_vec(nums);
  assert!(!sum.is_ok());
}
```

---

##### Change type of error when propagating Result up the stack
```rust
fn to_int(num: &str) -> Result<i32, ParseIntError> {
  num.parse()
}

fn sum_str_vec(nums: Vec<String>) -> Result<String, SumError> {
  let mut accum = 0i32;
  for num in nums {
    accum += to_int(&num).map_err(|_| SumError)?;
  }

  Ok(accum.to_string())
}
```


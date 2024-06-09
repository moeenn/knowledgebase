```rust
fn sum(a: i32, b: i32, c: i32) -> i32 {
  a + b + c
}

#[test]
fn test_sum() {
  assert_eq!(sum(20, 30, 40), 90);
  assert_eq!(sum(5,15,-5), 15);
}
```

The tests will not be run during normal compilation (debug or release). They can be executed using the following command

```bash
$ cargo test
```

#### Asserts
Asserts can be used to quickly test conditions. When assertions fail the program exists with a `panic`. There are two types of Asserts

- `assert!()` - This will always be checked during runtime regardless of whether the program is compiled in debug or release mode.

- `debug_assert!()` - These assertions are only checked during runtime when the program is compiled in debug mode.

```rust
fn main() {
  display(5);
}

fn display(a: u8) {
  assert!(a > 10);
  println!("All OK");
}
```
```bash
# installs globally
$ cargo install wasm-pack
```

`wasm-pack` is a compiler which needs to be installed globally. It will allow us to compile Rust library crates to web assembly.

---

#### Basic Example

```bash
# initialize library package
$ cargo init --lib
```

Update the default `Cargo.toml` file as follows.

```toml
[package]
name = "wasm_sandbox"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["cdylib"]

[profile.release]
lto = true

[dependencies]
wasm-bindgen = "0.2"
```

Update the default `lib.rs` file as follows.

```rust
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
extern {
	/* signatures of external JS functions */ 
    pub fn alert(s: &str);
}

#[wasm_bindgen]
pub fn greet(name: &str) {
    let msg = format!("Hello, {}!", name);
    alert(&msg);
}
```

Build the project using the following command

```bash
$ wasm-pack build --target web

# we can also specify an output directory and name
$ wasm-pack build --target web --out-dir ./some/nested/path --out-name index
```

The above command will generate files in directory `pkg`.  Notable thing is that it generates an ES Module file which can be used directly inside our front-end as follows.

```js
import init, { greet } from "./pkg/wasm_sandbox.js"
init().then(() => {
	greet("Random User")
})
```


---

#### Defining nested functions

```rust
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
extern {
    #[wasm_bindgen(js_namespace = console)]
    pub fn log(s: &str);

    #[wasm_bindgen(js_namespace = console, js_name = log)]
    pub fn log_nums(x: i32, y: i32);

}

#[wasm_bindgen]
pub fn greet(name: &str) {
    let msg = format!("Hello, {}!", name);
    log(&msg);
    log_nums(10, 20);
}

```
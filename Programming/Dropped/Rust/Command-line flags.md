
```bash
$ cargo add clap --features derive
```


#### Basic usage

```rust
use clap::Parser;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    #[arg(short, long)]
    template: String,

    #[arg(short, long)]
    name: String,
}

fn main() {
    let args = Args::parse();
    println!("template: {}, name: {}", args.template, args.name);
}
```
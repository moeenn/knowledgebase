```rust
use std::f64::consts::PI;

fn main() {
    // square int
    let base: i32 = 30;
    assert_eq!(base.pow(2), 900);

    // square root of float, ints must be cast to float before square root
    let squared: f32 = 100.0;
    assert_eq!(squared.sqrt(), 10.0);

    // calculate cube root
    let cubed: f64 = 64.0;
    assert_eq!(cubed.powf(1.0 / 3.0), 4.0);

    // rounding, (can be used as functions or methods)
    let num = 140.45_f64;
    assert_eq!(num.floor(), 140.0);
    assert_eq!(f64::ceil(15.6), 16.0);
    assert_eq!(f64::round(50.5), 51.0);
    assert_eq!(-20.5_f64.abs(), 20.5);

    // logs and exponents
    println!("{}", 1.0_f64.exp());
    println!("{}", 1.0_f64.ln()); // natural log
    println!("{}", 100.0_f32.log10());

    // basic trig functions, provide args in radians
    assert_eq!(f64::sin(PI / 2.0), 1.0);
    assert_eq!(f64::cos(2.0 * PI), 0.0);
    assert_eq!(f64::tan(PI / 4.0), 1.0);

    // trig functions are also available as f64 methods
    let theta = 2.0 * PI;
    assert_eq!(theta.sin(), 0.0);

    // trig inverse functions
    // cosec -> asin
    println!("{}", f64::asin(PI));
    // secant -> acos
    println!("{}", f64::acos(PI));
    // cotan -> atan
    println!("{}", f64::atan(PI));

    // TODO: hyperbolic trig functions

    // check if not a number (NAN)
    assert!(f64::is_nan(f64::NAN));
    assert!(!30.5_f32.is_nan());
}
```


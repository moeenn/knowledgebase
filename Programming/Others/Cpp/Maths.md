```cpp
#include <cmath>
#include <iomanip>
#include <iostream>

/* no built-in function for returning PI */
double pi() { return std::atan(1.0) * 4; }

/* convert degrees to radians */
double radians(const double &deg) { return deg * (pi() / 180); }

/* expected types: int, uint, float, double */
struct math_operation {
  const char *description;
  double number;
};

math_operation operations[] = {
    /* power functions */
    {"power :: 2^8\t", std::pow(2, 8)},
    {"square root :: 36", std::sqrt(36)},
    {"cube root :: 1000", std::cbrt(1000)},

    /* trigonometric functions (value of x in RADs) */ 
    {"sine :: 90 degrees", std::sin(radians(90))},
    {"cosine :: 90 degrees", std::cos(radians(90))},
    {"tangent :: 90 degrees", std::tan(radians(90))},

    /* inverse trigonometric functions*/ 
    /* inverse sine :: sin^(-1) 90 degrees :: 1 / sin 90 */ 
    {"cosec :: 90 degrees ", std::asin(radians(90))},
    /* inverse of cos :: cos^(-1) 90 degrees :: 1 / cos 90 */ 
    {"secant :: 90 degrees", std::acos(radians(90))},
    /* inverse of tan :: tan^(-1) 90 degrees :: 1 / tan 90 */ 
    {"cotan :: 90 degrees", std::atan(radians(90))},

    /* exponentiation and logs */ 
    {"exponentiate :: e^10", std::exp(10)},
    {"log :: log base e (200)", std::log(200)},
    {"log :: log base 10 (20)", std::log10(20)},

    /* integer operations */ 
    {"ceiling :: 3.52\t", std::ceil(3.52f)},
    {"floor :: 3.52\t", std::floor(3.52f)},
    {"round :: 3.52\t", std::round(3.52f)},
    {"remainder :: 100 % 3", std::fmod(100, 3)},
    {"remainder :: 100 % 3", std::remainder(10, 3)},

    /* removes the negative sign if negative */ 
    {"absolute :: -100.4", std::abs(-100.4)},
    /* NaN == Not a Number. Returns 1 (int) if true */ 
    {"check NaN :: 202", std::isnan(202)},
};

int main() {
  for (const auto &math_operation : operations) {
    std::printf("%s\t\t%.3f\n", math_operation.description,
                math_operation.number);
  }
}

/*
power :: 2^8                            32.000
square root :: 36                       6.000
cube root :: 1000                       10.000
sine :: 90 degrees                      0.000
cosine :: 90 degrees                    0.000
tangent :: 90 degrees                   0.000
cosec :: 90 degrees                     nan
secant :: 90 degrees                    nan
cotan :: 90 degrees                     1.263
exponentiate :: e^10                    22026.466
log :: log base e (200)                 5.298
log :: log base 10 (20)                 1.301
ceiling :: 3.52                         4.000
floor :: 3.52                           3.000
round :: 3.52                           4.000
remainder :: 100 % 3                    1.000
remainder :: 100 % 3                    1.000
absolute :: -100.4                      100.400
check NaN :: 202                        0.000
*/
```


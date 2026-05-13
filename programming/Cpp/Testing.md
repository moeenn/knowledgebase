#### Asserts
Assertions can be used to quickly verify conditions. If the assertion fails the program will terminate and state the assertion that failed. Assertions are used for debugging and are not generally used for user input validations.

```cpp
#include <cassert>

void total(int a, int b) {
  assert(a != 0 && b != 0);
  std::cout << a + b << '\n';
}

int main() {
  total(10, 0);
}
```

The Assertions in the above code are **performed at Runtime**. This means that there is a slight Performance Penalty because the Assertion will be checked every time the program is executed.

If we need to perform Assertion checking at Compile Time we can use `static_assert`. This function uses constant expressions (i.e. `constexpr`) and takes in a second argument specifying the error message in case the static assertion fails. The build will fail if one or more Static Assertions fail.

```cpp
#include <iostream>


#define LOG(msg) std::cout << msg << '\n'

constexpr unsigned int factorial(const unsigned int& number) {
  if(number == 0) return 1;

  uint retval = 1;
  for(int i = 2; i <= number; i++)
    retval *= i;

  return retval;
}

void test_factorial() {
  static_assert(factorial(0) == 1, "Test failed :: 0! != 1");
  static_assert(factorial(1) == 1, "Test failed :: 1! != 1");
  static_assert(factorial(3) == 6, "Test failed :: 3! != 6");
  static_assert(factorial(8) == 40320, "Test failed :: 8! != 40320");
  LOG("factorial() :: All tests Passed!");
}

int main() {
  test_factorial();
}
```

**Note**: `static_assert` is interesting because it is neither included in the std namespace nor does it require any library to be included.

#### Pseudo-random numbers

```cpp
#include <iostream>
#include <ctime>

Int main() {
  /* randomize seed: don’t randomize more than once */ 
  std::srand{time(NULL)};
  const int num = std::rand() % 50 + 10;

  std::cout << num << "\n";
}
/* generate numbers in range [10,60) */
```

```cpp
#include <iostream>
#include <ctime>

namespace Random {
  bool m_seed_set{false};

  int randInt(const int& floor, const int& ceil) {
    if(!m_seed_set) {
      std::srand(time(NULL));
      m_seed_set = true;
    }
    return std::rand() % (ceil - floor) + floor;
  }
}

int main() {
  for(uint i = 0; i < 100; i++) {
    std::cout << Random::randInt(50, 100) << "\t";
    if ((i + 1) % 10 == 0) std::cout << '\n';
  }
}
```


---

#### Random numbers in normal (gaussian) distribution

```cpp
#include <iostream>
#include <random>

int main() { 
  /** 
   * random_device is used to generate a random seed. This should not be used
   * repeatedly.
  */
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution(1, 10);

  for (int i = 0; i < 100; i++) {
    std::cout << distribution(generator) << " ";
  }  

  std::cout << "\n";
}
```

**Note**: If we need to generate the same range on every execution, we can do something like this.

```cpp
std::mt19937 generator(0);
```


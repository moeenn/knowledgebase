
#### Loops

```cpp
#include <iostream>
#include <vector>
#include <functional>

template<typename T>
void for_each(const std::vector<T> &input, std::function<void(T)> callback) {
  if (input.size() == 0) {
    return;
  }

  callback(input[0]);
  for_each(std::vector<T>(input.begin()+1, input.end()), callback);
}

int main() {
  std::vector<int> nums {1,2,3,4,5};
  for_each<int>(nums, [](int n) {
    std::cout << n << "\n";
  });
}
```
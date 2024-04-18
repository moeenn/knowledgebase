```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>

std::optional<std::string> read_file(const std::string& path) {
  std::ifstream file{path};

  if (!file.is_open()) {
    return {};
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  file.close();
  return buffer.str();
}

int main() {
  std::optional<std::string> content = read_file("./sample.txt");
  
  if (!content) {
    std::cerr << "Failed to read file \n";
    return 1;
  }

  std::cout << *content << '\n';
}
```

```cpp
#include <iostream>
#include <optional>

auto process(uint n) -> std::optional<int> {
  if (n == 200) return {};
  return n * 10;
}

auto main() -> int { 
  auto result = process(200).value_or(0);
  std::cout << "result: " << result << "\n"; 
}
```

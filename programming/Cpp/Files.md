
#### Reading files

```cpp
#include <fstream>
#include <iostream>
#include <optional>

std::optional<std::string> read_file(const std::string &filename) {
  std::ifstream file{filename};

  if (!file) {
    return {};
  }

  std::string file_content;
  while (file) {
    std::string line;
    std::getline(file, line);
    file_content += line + "\n";
  }

  /* close file to prevent data corruption and vulnerabilities */
  file.close();
  return file_content;
}

int main() {
  std::optional<std::string> content = read_file("examples.txt");
  if (!content) {
    std::cerr << "[error] failed to read file content\n";
    return 1;
  }

  std::cout << *content;
}
```


---

#### Writing files

```cpp
void writeFile(const std::string& filename, const std::string& line) {
  std::ofstream file(filename, std::ios::app);
  file << line << "\n";
  file.close();
}
```

Note: 
- The file will be created if it doesn’t exist. The content is appended (`ios::app`) to the file.
- Both `ifstream` and `ofstream` objects have a method open() for specifying file names and read-modes. It is useful when creating a file object using the default constructor  
- In the examples `std::string` have been passed as `const references` to the function to prevent unnecessary and costly copy operations.



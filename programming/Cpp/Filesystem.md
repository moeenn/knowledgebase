```cpp
#include <filesystem>
#include <iostream>

int main() {
  const char* path = "./bin";
  bool flag = std::filesystem::is_directory(path);

  std::cout << std::boolalpha
            << "[exists] " << flag << "\n";
}
```

**Note**: The `std::filesystem` requires C++17 and above.

The namespace may become tedious to type, we can define an alias for the namespace

```cpp
namespace fs = std::filesystem;
...
fs::is_directory(path)
```

Reference: [Link](https://en.cppreference.com/w/cpp/filesystem)

---

#### Usage

```cpp
// Check if path is a directory
std::filesystem::is_directory(path)


// get content of a directory
const char* path = "./src";

for (const auto& item : std::filesystem::directory_iterator(path)) {
  std::cout << item.path() << '\n';
}


// Get content of directory and all its sub-directories
const char* path = "./src";

for (const auto& item : std::filesystem::recursive_directory_iterator(path)) {
  std::cout << item.path() << '\n';
}


// create new directory
std::filesystem::create_directory(path)


// copy content of a directory
const char* path = "./example/01";
const char* target = "./example/02";

std::filesystem::copy(
  path,
  target,
  std::filesystem::copy_options::recursive
);


// rename file or directory
const char* in = "./example/01";
const char* out = "./example/02";

std::filesystem::rename(in, out);


// delete file or empty directory
const char* in = "./example/02";
std::filesystem::remove(in);

// Note: This is nice because it will throw if the directory is not empty. If we // don’t care, we can remove a directory with all its content recursively using // the following

std::filesystem::remove_all(in);
```

### Files

#### Reading files

```cpp
#include <fstream>
#include <iostream>
#include <optional>

std::optional<std::string> readFile(const std::string &filename) {
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

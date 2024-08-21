```cpp
#include <iostream>
#include <optional>
#include <string>

// jenkin's hash function
uint32_t hash(const std::string &key) {
  uint32_t h = 0;

  for (char c : key) {
    h += (uint32_t)c;
    h += h << 10;
    h ^= h >> 6;
  }

  h += h << 3;
  h ^= h >> 11;
  h += h << 15;

  return h;
}

template <typename T> class Node {
public:
  std::string key;
  T value;
  std::shared_ptr<Node<T>> next;

  Node(const std::string &key, T value, std::shared_ptr<Node<T>> next) {
    this->key = key;
    this->value = value;
    this->next = next;
  }
};

template <typename T, size_t N> class HashMap {
private:
  std::shared_ptr<Node<T>> m_data[N];

  size_t get_index(const std::string &key) const {
    uint32_t h = hash(key);
    return h % N;
  }

public:
  HashMap() {
    size_t i;
    for (i = 0; i < N; i++) {
      m_data[i] = nullptr;
    }
  }

  void set(std::string key, T value) {
    size_t index = get_index(key);

    // case one: list at index is empty
    if (m_data[index] == nullptr) {
      std::shared_ptr<Node<T>> new_node =
          std::make_shared<Node<T>>(key, value, nullptr);
      m_data[index] = new_node;
    } else {
      // case two: list at index is not empty
      std::shared_ptr<Node<T>> current = m_data[index];
      for (; current != nullptr; current = current->next) {
        // case: key could already exist, making it an update operation
        if (current->key == key) {
          current->value = value;
          return;
        }
      }

      std::shared_ptr<Node<T>> new_node =
          std::make_shared<Node<T>>(key, value, nullptr);
      current->next = new_node;
    }
  }

  std::optional<T> get(std::string key) {
    size_t i;
    std::shared_ptr<Node<T>> current = nullptr;

    for (i = 0; i < N; i++) {
      current = m_data[i];
      for (; current != nullptr; current = current->next) {
        if (current->key == key) {
          return current->value;
        }
      }
    }

    return {};
  }

  void clear() {
    std::shared_ptr<Node<T>> next = nullptr;
    std::shared_ptr<Node<T>> current = nullptr;
    size_t index;

    for (index = 0; index < N; index++) {
      m_data[index] = nullptr;
    }
  }

  ~HashMap() { clear(); }
};
```
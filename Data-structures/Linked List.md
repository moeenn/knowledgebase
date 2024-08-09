
#### To-do

  - [x] Singly-linked list
  - [ ] Doubly-linked list


---

#### Singly-linked list

```cpp
#include <iostream>
#include <optional>
#include <vector>

template <typename T> class Node {
public:
  T data;
  std::shared_ptr<Node<T>> next;

  Node(T data, std::shared_ptr<Node<T>> next) {
    this->data = data;
    this->next = next;
  }

  ~Node() { std::cout << "destroying: " << data << "\n"; }
};

template <typename T> class LinkedList {
private:
  std::shared_ptr<Node<T>> m_head;

public:
  LinkedList() { m_head = nullptr; }

  void append(T data) {
    std::shared_ptr<Node<int>> new_node =
        std::make_shared<Node<int>>(data, nullptr);

    // case one: list was empty
    if (m_head == nullptr) {
      m_head = new_node;
      return;
    }

    // case two: list had elements
    std::shared_ptr<Node<T>> current = m_head;
    for (; current->next != nullptr; current = current->next) {
    }
    current->next = new_node;
  }

  void prepend(T data) {
    std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(data, m_head);
    m_head = new_node;
  }

  void iterate(std::function<void(T)> fn) {
    std::shared_ptr<Node<T>> current = m_head;
    for (; current != nullptr; current = current->next) {
      fn(current->data);
    }
  }

  size_t size() const {
    size_t i = 0;
    std::shared_ptr<Node<T>> current = m_head;
    for (; current != nullptr; current = current->next) {
      i++;
    }
    return i;
  }

  std::vector<int> to_vector() {
    std::vector<T> result;
    size_t size = this->size();
    if (size == 0) {
      return result;
    }
    result.reserve(size);

    this->iterate([&result](T data) { result.push_back(data); });
    return result;
  }

  std::optional<T> at(size_t index) {
    size_t i = 0;
    std::shared_ptr<Node<T>> current = m_head;
    for (; current != nullptr; current = current->next) {
      if (i == index) {
        return current->data;
      }
      i++;
    }
    return {};
  }

  bool contains(T data) {
    std::shared_ptr<Node<T>> current = m_head;
    for (; current != nullptr; current = current->next) {
      if (current->data == data) {
        return true;
      }
    }
    return false;
  }

  bool remove(size_t index) {
    size_t i = 0;
    std::shared_ptr<Node<T>> current = m_head;
    std::shared_ptr<Node<T>> prev = nullptr;

    // case one: deleting first element
    if (index == 0) {
      if (m_head != nullptr && m_head->next != nullptr) {
        std::shared_ptr<Node<T>> next = m_head->next;
        m_head = next;
        return true;
      }
      return false; // list was empty
    }

    // case two: deleting element at index other than 0
    for (; current != nullptr; current = current->next) {
      if (i == index) {
        prev->next = current->next;
        return true;
      }

      prev = current;
      i++;
    }

    return false;
  }

  // TODO: this destructor is no-longer required because head is a shared_ptr
  ~LinkedList() {
    std::shared_ptr<Node<T>> next = nullptr;
    std::shared_ptr<Node<T>> current = m_head;
    for (; current != nullptr; current = next) {
      next = current->next;
    }
  }
};
```
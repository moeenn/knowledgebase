
```cpp
#include <cassert>
#include <iostream>
#include <optional>

template <typename T, size_t N>
class Stack {
private:
  T m_data[N];
  size_t m_current_idx = 0;

public:
  bool push(T item) {
    if (m_current_idx == N) {
      return false;
    }
    m_data[m_current_idx++] = item;
    return true;
  }

  std::optional<T> peek() {
    if (m_current_idx == 0) {
      return {};
    }
    return m_data[m_current_idx - 1];
  }

  std::optional<T> pop() {
    if (m_current_idx == 0) {
      return {};
    }
    return m_data[--m_current_idx];
  }

  size_t size() const {
    return m_current_idx;
  }
};
```

```cpp
void test_stack() {
  Stack<int, 4> s;
  s.push(10);
  s.push(20);
  s.push(30);

  assert(s.size() == 3);
  assert(s.peek() == 30);
  assert(s.pop() == 30);
  assert(s.size() == 2);
  assert(s.peek() == 20);

  s.push(100);
  s.push(200);
  assert(s.size() == 4);
  assert(!s.push(1000));

  for (int i = 0; i < 4; i++) {
    s.pop();
  }
  assert(s.size() == 0);
  assert(!s.pop().has_value());
}
```
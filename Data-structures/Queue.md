#### To-do

- [ ] Priority queues


---


```cpp
#include <cassert>
#include <iostream>
#include <optional>

template <typename T, size_t N> class Queue {
private:
  T m_data[N];
  size_t m_front = 0;
  size_t m_back = 0;

public:
  bool enqueue(T item) {
    if (is_full()) {
      return false;
    }
    m_data[m_back++] = item;
    return true;
  }

  std::optional<T> dequeue() {
    if (is_empty()) {
      return {};
    }
    T value = m_data[m_front++];

    if (m_front == m_back) {
      m_front = m_back = 0;
    }

    return value;
  }

  bool is_empty() const { return m_front == 0 && m_back == 0; }

  bool is_full() const { return m_back == N; }

  std::optional<T> peek() const {
    if (is_empty()) {
      return {};
    };

    return m_data[m_front];
  }
};
```

```cpp
void test_queue() {
  Queue<int, 3> q;
  assert(q.is_empty());
  assert(!q.is_full());
  q.enqueue(10);
  q.enqueue(20);

  assert(q.enqueue(30));
  assert(!q.enqueue(40));
  assert(q.is_full());
  assert(q.dequeue().value() == 10);
  assert(q.dequeue().value() == 20);
  assert(q.dequeue().value() == 30);
  assert(!q.dequeue().has_value());
  assert(q.is_empty());
  assert(q.enqueue(100));
  assert(q.peek() == 100);
  assert(q.peek() == 100);
}
```
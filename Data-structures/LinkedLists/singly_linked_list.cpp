#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>

template <typename T> class Node
{
public:
  T m_data;
  std::shared_ptr<Node<T>> m_next;

  explicit Node(const T &data, std::shared_ptr<Node<T>> next = nullptr)
  {
    m_data = data;
    m_next = next;
  }

  // disable copy operations.
  Node(const Node &other) = delete;
  Node &operator=(const Node &) = delete;
};

template <typename T> class LinkedList
{
private:
  std::shared_ptr<Node<T>> m_head;
  size_t m_size;

public:
  LinkedList() noexcept
  {
    m_size = 0;
    m_head = nullptr;
  }

  // disable copy operations.
  LinkedList(const LinkedList &) = delete;
  LinkedList &operator=(const LinkedList &) = delete;

  size_t size() const noexcept
  {
    return m_size;
  }

  void append(const T &data) noexcept
  {
    std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(data);
    if (m_head == nullptr)
    {
      m_head = new_node;
      m_size++;
      return;
    }

    std::shared_ptr<Node<T>> current = m_head;
    for (; current->m_next != nullptr; current = current->m_next)
    {
    }

    current->m_next = new_node;
    m_size++;
  }

  void prepend(const T &data) noexcept
  {
    auto new_node = std::make_shared<Node<T>>(data, m_head);
    m_head = new_node;
    m_size++;
  }

  void iter(std::function<void(const T &, const size_t)> callback) const noexcept
  {
    std::shared_ptr<Node<T>> current = m_head;
    size_t i = 0;

    for (; current != nullptr; current = current->m_next)
    {
      callback(current->m_data, i);
      i++;
    }
  }

  std::optional<const T> at(const size_t index) const noexcept
  {
    if (index >= m_size)
    {
      return {};
    }

    std::optional<T> result = {};
    iter([&result, index](const T &v, size_t i) {
      if (i == index)
      {
        result = v;
      }
    });

    return result;
  }

  bool remove(const size_t index) noexcept
  {
    if (m_size == 0 || index >= m_size)
    {
      return {};
    }

    size_t i = 0;
    std::shared_ptr<Node<T>> current = m_head;
    std::shared_ptr<Node<T>> prev = nullptr;

    for (; current != nullptr; current = current->m_next)
    {
      // dropping head.
      if (index == 0 && i == 1)
      {
        m_head = current;
        m_size--;
        return true;
      }

      // dropping any other index.
      if (i == index && prev != nullptr)
      {
        prev->m_next = current->m_next;
        m_size--;
        return true;
      }

      prev = current;
      i++;
    }

    return false;
  }
};

void test_linked_list()
{
  /* test basic operations */ {
    LinkedList<int> nums{};
    nums.append(10);
    nums.append(20);
    nums.append(30);
    nums.append(40);
    nums.prepend(100);

    assert(nums.size() == 5);
    std::optional<int> first = nums.at(0);
    assert(first.has_value());
    assert(first.value() == 100);

    std::optional<int> last = nums.at(4);
    assert(last.has_value());
    assert(last.value() == 40);

    std::optional<int> out_of_bounds = nums.at(100);
    assert(!out_of_bounds.has_value());

    bool is_removed = nums.remove(1);
    assert(is_removed);
    assert(nums.size() == 4);

    std::optional<int> at_one = nums.at(1);
    assert(at_one.value() != 10);
    assert(at_one.value() == 20);

    bool is_not_removed = nums.remove(200);
    assert(!is_not_removed);
    assert(nums.size() == 4);
  }

  /* test operations on empty list. */ {
    LinkedList<int> empty{};
    assert(empty.size() == 0);

    int invoke_count{0};
    empty.iter([&invoke_count](const int &n, size_t index) {
      std::cout << n << ", " << index << "\n";
      invoke_count++;
    });
    assert(invoke_count == 0);

    bool is_removed = empty.remove(0);
    assert(!is_removed);
    assert(empty.size() == 0);
  }
}

typedef std::function<void()> Test;
std::array<Test, 1> tests{
  test_linked_list,
};

void run_tests()
{
  for (const auto &test : tests)
  {
    test();
  }
  std::cout << "-- all tests pass --\n";
}


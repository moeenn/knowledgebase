
#### To-do

  - [x] Binary search
  - [ ] Depth-first search (DFS)
  - [ ] Breadth-first search (BFS)


---

#### Binary search

```cpp
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

std::optional<size_t> binary_search(const std::vector<int> &nums, int target) {
  assert(nums.size() > 2);
  int start = 0;
  int end = nums.size() - 1;
  int mid = 0;
  size_t iter = 0;

  if (nums[start] > target) {
    return {};
  }

  while (start <= end) {
    assert(iter++ < nums.size());
    mid = (start + end) / 2;

    if (nums[mid] == target) {
      return mid;
    }

    if (nums[mid] > target) {
      end = mid;
    }

    if (nums[mid] < target) {
      start = mid + 1;
    }
  }

  return {};
}
```

```cpp
void test_binary_search() {
  struct TestCase {
    std::vector<int> nums;
    int target;
    std::optional<int> expected;
  };

  const TestCase test_cases[] = {
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 3,
      .expected = std::optional<int>{2},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 4,
      .expected = std::optional<int>{3},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 2,
      .expected = std::optional<int>{1},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 5,
      .expected = std::optional<int>{4},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 1,
      .expected = std::optional<int>{0},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = 10,
      .expected = std::optional<int>{},
    },
    {
      .nums = std::vector<int>{1, 2, 3, 4, 5},
      .target = -200,
      .expected = std::optional<int>{},
    },
  };

  for (const TestCase &testcase : test_cases) {
    std::optional<int> got = binary_search(testcase.nums, testcase.target);
    if (testcase.expected.has_value()) {
      assert(testcase.expected.value() == got.value());
    }

    if (!testcase.expected.has_value()) {
      assert(!got.has_value());
    }
  }
}
```



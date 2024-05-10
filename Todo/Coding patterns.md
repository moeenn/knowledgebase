#### Todo
- [ ] Linked lists
- [ ] Hash-maps
- [ ] Trees
- [ ] Graphs
- [ ] Common algorithms
    - [ ] Search
        - [x] Binary search
        - [ ] Depth-first search (DFS)
        - [ ] Breadth-first search (BFS)
    - [ ] Sorting
        - [ ] Insertion sort
        - [ ] Merge sort
        - [ ] Quick sort
    - [ ] Greedy algorithm
- [ ] [Coding patterns](https://levelup.gitconnected.com/dont-just-leetcode-follow-the-coding-patterns-instead-4beb6a197fdb)
- [ ] [Big-O notation]([https://www.baeldung.com/cs/big-oh-asymptotic-complexity](https://www.baeldung.com/cs/big-oh-asymptotic-complexity))
    - [ ] [Link](https://www.simplilearn.com/big-o-notation-in-data-structure-article#:~:text=For%20example%3A,-O(1)%20represents&text=O(n)%20represents%20linear%20time,exponentially%20with%20the%20input%20size.)
    - [ ] [Link](https://developerinsider.co/big-o-notation-explained-with-examples/)



##### Binary search

```cpp
int binary_search(const std::vector<int> &nums, int target) {
  assert(nums.size() > 1);
  int start = 0;
  int end = nums.size();
  int mid;

  while (start < end) {
    mid = (start + end) / 2;

    if (nums[start] == target) return start;
    if (nums[end] == target) return end;
    if (nums[mid] == target) return mid;

    if (nums[mid] > target) {
      end = mid - 1;
    }

    if (nums[mid] < target) {
      start = mid + 1;
    }
  }

  return -1;
}
```

```cpp
struct TestCase {
  std::vector<int> nums;
  int target;
  int result;
};

void test_binary_search() {
  std::array<TestCase, 2> testCases{
    TestCase{
        .nums = {1, 2, 3, 4, 5},
        .target = 3,
        .result = 2,
    },
    TestCase{
        .nums = {1, 2, 3, 4, 5, 6},
        .target = 1,
        .result = 0,
    },
  };

  for (const TestCase &testCase : testCases) {
    int result = binary_search(testCase.nums, testCase.target);
    assert(result == testCase.result);
  }

  std::cout << "test_binary_search passes\n";
}
```
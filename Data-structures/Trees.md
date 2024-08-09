
#### To-do

  - [x] Binary tree
  - [ ] Binary search tree
  - [ ] AVL tree
  - [ ] B-Tree


---

#### Binary tree

```cpp
/** helper functions */
bool x_or(bool one, bool two) {
  if (one && !two)
    return true;
  if (!one && two)
    return true;
  return false;
}
```

```cpp
#include <functional>
#include <iostream>
#include <memory>

/**
 * There are three different methods of traversal
 * InOrder: Left, Data, Right
 * PreOrder: Data, Left, Right
 * PostOrder: Left, Right, Data
 */
enum class TreeTraversalOrder {
  InOrder,
  PreOrder,
  PostOrder,
};

template <typename T> class Node {
public:
  T data;
  std::shared_ptr<Node<T>> left;
  std::shared_ptr<Node<T>> right;

  Node(T data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
  }
};

template <typename T> class BinaryTree {
private:
  std::shared_ptr<Node<T>> root;

public:
  BinaryTree(std::shared_ptr<Node<T>> root) { this->root = root; }

  void traverseNodes(TreeTraversalOrder order, std::function<void(T)> cb) {
    std::function<void(std::shared_ptr<Node<T>>)> traverse =
        [&traverse, &cb, &order](std ::shared_ptr<Node<T>> node) {
          if (node == nullptr) {
            return;
          }

          switch (order) {
          case TreeTraversalOrder::InOrder:
            traverse(node->left);
            cb(node->data);
            traverse(node->right);
            break;

          case TreeTraversalOrder::PreOrder:
            cb(node->data);
            traverse(node->left);
            traverse(node->right);
            break;

          case TreeTraversalOrder::PostOrder:
            traverse(node->left);
            traverse(node->right);
            cb(node->data);
            break;
          }
        };

    traverse(root);
  }

  /**
   * A full Binary tree is a special type of binary tree in which every parent
   * node/internal node has either two or no children.
   */
  bool is_full() {
    std::function<bool(std::shared_ptr<Node<T>>)> traverse =
        [&traverse](std::shared_ptr<Node<T>> node) -> bool {
      if (node->left == nullptr && node->right == nullptr) {
        return true;
      }

      if (x_or(node->left == nullptr, node->right == nullptr)) {
        return false;
      }

      return traverse(node->left) && traverse(node->right);
    };

    return traverse(root);
  }
};

int main() {
  std::shared_ptr<Node<int>> root = std::make_shared<Node<int>>(10);
  BinaryTree tree(root);

  root->left = std::make_shared<Node<int>>(20);
  root->right = std::make_shared<Node<int>>(30);

  root->left->left = std::make_shared<Node<int>>(40);
  root->left->right = std::make_shared<Node<int>>(50);

  tree.traverseNodes(TreeTraversalOrder::PreOrder,
                     [](int n) { std::cout << n << "\n"; });
}
```
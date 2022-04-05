#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* curr = find(key, root_);
    if (curr == nullptr){
      return std::nullopt;
    }
    return curr -> value;
  }

  bool BinarySearchTree::Contains(int key) const {
    if (Find(key) == std::nullopt){
      return false;
    }
    return true;
  }

  bool BinarySearchTree::IsEmpty() const {

    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    Node* curr_node = root_;

    while (curr_node->left != nullptr) {
      curr_node = curr_node->left;
    }
    return curr_node->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ != nullptr) {
      Node* curr = root_;
      while (curr -> right != nullptr) {
        curr = curr -> right;
      }
      return curr -> value;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      Node* new_node = new Node(key, value);
      node = new_node;
    }
    else {
      if (key < node -> key) {
        insert(key, value, node -> left);
      }
      else if (key == node -> key) {
        node -> value = value;
      }
      else {
        insert(key, value, node -> right);
      }
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node != nullptr) {
      if (key < node -> key) {
        return remove(key, node -> left);
      }
      if (key == node->key) {
        if (node->left != nullptr and node->right != nullptr) {
          Node* min_node = find_min(node->right);
          node -> key = min_node -> key;
          node -> value = min_node -> value;
          return remove(min_node -> key, node -> right);
        }
        if (node->left != nullptr and node->right == nullptr) {
          Node* left_child = node -> left;
          delete node;
          node = left_child;
          return true;
        }
        Node* right_node = node -> right;
        delete node;
        node = right_node;
        return true;
      }
      return remove(key, node -> right);
    }
    return false;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (key == node->key) {
      return node;
    }
    if (key < node->key) {
      return find(key, node->left);
    }
    if (key > node->key) {
      return find(key, node->right);
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    while(node -> left != nullptr) {
      node = node -> left;
    }
    return node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    while(node -> right != nullptr) {
      node = node -> right;
    }
    return node;
  }

}  // namespace assignment
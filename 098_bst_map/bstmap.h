#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"
using namespace std;
template<typename K, typename V>
class BstMap : public Map<K, V> {
 public:
  class Node {
   public:
    K key;
    V value;
    Node *left, *right;
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & b) { root = copy(b.root); }
  Node * copy(const Node * n2) {
    if (n2 == NULL) {
      return NULL;
    }
    Node * n1 = new Node(n2->key, n2->value);
    n1->left = copy(n2->left);
    n1->right = copy(n2->right);
    return n1;
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      swap(root, temp.root);
      //copy(&root, rhs.root);
    }
    return *this;
  }
  //add
  virtual void add(const K & key, const V & value) {
    Node * curr = root;
    if (curr == NULL) {
      root = new Node(key, value);
      return;
    }
    while (curr != NULL) {
      if (curr->key == key) {
        curr->value = value;
        return;
      }
      else if (curr->key < key) {
        if (curr->right == NULL) {
          curr->right = new Node(key, value);
          return;
        }
        curr = curr->right;
      }
      else if (curr->key > key) {
        if (curr->left == NULL) {
          curr->left = new Node(key, value);
          return;
        }
        curr = curr->left;
      }
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      else if (curr->key < key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    throw std::invalid_argument("cannot lookup key");
  }

  void destroy(Node * n) {
    if (n == NULL) {
      return;
    }
    destroy(n->left);
    destroy(n->right);
    delete n;
  }
  virtual void remove(const K & key) {
    Node ** curr = &root;
    while ((*curr) != NULL) {
      if (key == (*curr)->key) {
        break;
      }
      else if (key > (*curr)->key) {
        curr = &((*curr)->right);
      }
      else {
        curr = &((*curr)->left);
      }
    }
    if ((*curr) == NULL) {
      //return;
      //throw?
      throw std::invalid_argument("cannot remove key");
    }
    else if ((*curr)->left == NULL) {
      Node * temp = (*curr)->right;
      delete (*curr);
      *curr = temp;
      return;
    }
    else if ((*curr)->right == NULL) {
      Node * temp = (*curr)->left;
      delete (*curr);
      (*curr) = temp;
      return;
    }
    else {
      Node * Rightmin = (*curr)->right;
      while (Rightmin->left != NULL) {
        Rightmin = Rightmin->left;
      }
      K tk = Rightmin->key;
      V tv = Rightmin->value;
      // Rightmin->key = (*curr)->key;
      //Rightmin->value = (*curr)->value;
      remove(Rightmin->key);

      (*curr)->key = tk;
      (*curr)->value = tv;
      //remove(Rightmin->key);
      return;
    }
  }
  Node * getRoot() { return root; }
  void printTree(Node * n) {
    if (n == NULL) {
      return;
    }
    printTree(n->left);
    cout << n->key << ":" << n->value << "\n";
    printTree(n->right);
  }
  virtual ~BstMap<K, V>() { destroy(root); }
};

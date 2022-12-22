
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "set.h"

using namespace std;

template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node *left, *right;
    Node(T t) : key(t), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  //constructor
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) { root = copy(rhs.root); }
  Node * copy(const Node * n2) {
    if (n2 == NULL) {
      return NULL;
    }
    Node * n1 = new Node(n2->key);
    n1->left = copy(n2->left);
    n1->right = copy(n2->right);
    return n1;
  }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet<T> temp(rhs);
      swap(root, temp.root);
    }
    return *this;
  }
  //add
  virtual void add(const T & key) {
    Node * curr = root;
    if (curr == NULL) {
      root = new Node(key);
      return;
    }
    while (curr != NULL) {
      if (curr->key == key) {
        return;
      }
      else if (curr->key < key) {
        if (curr->right == NULL) {
          curr->right = new Node(key);
          return;
        }
        curr = curr->right;
      }
      else if (curr->key > key) {
        if (curr->left == NULL) {
          curr->left = new Node(key);
          return;
        }
        curr = curr->left;
      }
    }
  }
  //contain
  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      else if (curr->key < key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    return false;
  }
  //remove
  virtual void remove(const T & key) {
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
      T tk = Rightmin->key;
      remove(Rightmin->key);
      (*curr)->key = tk;
      return;
    }
  }
  virtual ~BstSet<T>() { destroy(root); }
  void destroy(Node * n) {
    if (n == NULL) {
      return;
    }
    destroy(n->left);
    destroy(n->right);
    delete n;
  }
};

#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d) : data(d), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
    ~Node() {}
  };
  class WrongIndex : public std::exception {
    const char * what() { return "index out of bound"; }
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
    Node * n = rhs.head;
    while (n != NULL) {
      addBack(n->data);
      n = n->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * n = head->next;
        delete head;
        head = n;
      }
      head = NULL;
      tail = NULL;
      Node * c = rhs.head;
      while (c != NULL) {
        addBack(c->data);
        c = c->next;
      }
    }
    return *this;
  }
  void addFront(const T & item) {
    Node * n = new Node(item);
    if (head != NULL) {
      head->prev = n;
    }
    if (head == NULL) {
      tail = n;
    }
    n->prev = NULL;
    n->next = head;
    head = n;
  }
  void addBack(const T & item) {
    Node * n = new Node(item);
    if (tail != NULL) {
      tail->next = n;
    }
    if (tail == NULL) {
      head = n;
    }
    n->next = NULL;
    n->prev = tail;
    tail = n;
  }
  bool remove(const T & item) {
    Node * del = head;
    while (del != NULL) {
      if (del->data == item) {
        if (del == head) {
          head = head->next;
        }
        if (del == tail) {
          tail = tail->prev;
        }
        if (del->prev != NULL) {
          del->prev->next = del->next;
        }
        if (del->next != NULL) {
          del->next->prev = del->prev;
        }
        delete del;
        return true;
      }
      del = del->next;
    }
    return false;
  }
  T & operator[](int index) {
    Node * n = head;
    while (n != NULL) {
      if (index == 0) {
        return n->data;
      }
      index--;
      n = n->next;
    }
    throw WrongIndex();
  }
  const T & operator[](int index) const {
    Node * n = head;
    while (n != NULL) {
      if (index == 0) {
        return n->data;
      }
      index--;
      n = n->next;
    }
    throw WrongIndex();
  }
  int find(const T & item) const {
    Node * n = head;
    int i = 0;
    while (n != NULL) {
      if (n->data == item) {
        return i;
      }
      n = n->next;
      i++;
    }
    return -1;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  int getSize() const {
    Node * n = head;
    if (head == NULL) {
      return 0;
    }
    int i = 1;
    while (n != tail) {
      n = n->next;
      i++;
    }
    return i;
  };
  friend class Tester;
};

#endif

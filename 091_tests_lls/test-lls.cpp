#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(5);  //5
    assert(il.find(5) == 0);
    assert(il[0] == 5);
    assert(il.getSize() == 1);
    assert(il.head != NULL);
    assert(il.head->data == 5);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.head == il.tail);

    il.addFront(6);  //6 5
    assert(il.find(6) == 0);
    assert(il.find(5) == 1);
    assert(il[0] == 6);
    assert(il[1] == 5);
    assert(il.getSize() == 2);
    assert(il.head->data == 6);
    assert(il.tail->data == 5);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
  }
  void testAddBack() {
    // WRITE ME
    IntList il;
    il.addBack(5);  //5
    assert(il.getSize() == 1);
    assert(il.head != NULL);
    assert(il.head == il.tail);
    assert(il.head->data == 5);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);

    il.addBack(6);  //5 6
    assert(il.getSize() == 2);
    assert(il.find(5) == 0);
    assert(il.find(6) == 1);
    assert(il[0] == 5);
    assert(il[1] == 6);
    assert(il.head->data == 5);
    assert(il.tail->data == 6);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == il.head);
  }
  void testCopy() {
    IntList il1;
    il1.addBack(5);
    il1.addBack(6);
    il1.addBack(7);
    IntList il = IntList(il1);
    assert(il1.head != il.head);
    assert(il1.getSize() == 3 && il.getSize() == 3);
    assert(il1.find(5) == 0 && il.find(5) == 0);
    assert(il1.find(6) == 1 && il.find(6) == 1);
    assert(il1[0] == 5 && il[0] == 5);
    assert(il1[1] == 6 && il[1] == 6);
    assert(il1.head->data == 5 && il.head->data == 5);
    assert(il1.tail->data == 7 && il.tail->data == 7);
    assert(il1.head->next->next == il1.tail && il.head->next->next == il.tail);
    assert(il1.head->prev == NULL && il.head->prev == NULL);
    assert(il1.tail->next == NULL && il.tail->next == NULL);
    assert(il1.tail->prev->prev == il1.head && il.tail->prev->prev == il.head);
  }
  void testAssign() {
    IntList il1;
    il1.addBack(5);
    il1.addBack(6);
    il1.addBack(7);
    IntList il;
    il.addBack(4);
    il = il1;
    assert(il1.head != il.head);
    assert(il1.getSize() == 3 && il.getSize() == 3);
    assert(il1.find(5) == 0 && il.find(5) == 0);
    assert(il1.find(6) == 1 && il.find(6) == 1);
    assert(il1[0] == 5 && il[0] == 5);
    assert(il1[1] == 6 && il[1] == 6);
    assert(il1.head->data == 5 && il.head->data == 5);
    assert(il1.tail->data == 7 && il.tail->data == 7);
    assert(il1.head->next->next == il1.tail && il.head->next->next == il.tail);
    assert(il1.head->prev == NULL && il.head->prev == NULL);
    assert(il1.tail->next == NULL && il.tail->next == NULL);
    assert(il1.tail->prev->prev == il1.head && il.tail->prev->prev == il.head);
  }

  void testRemove() {
    IntList il;
    il.addBack(5);
    il.addBack(6);
    il.addBack(7);  // 5 6 7
    //did not remove
    bool success = il.remove(4);
    assert(!success);

    //remove front
    success = il.remove(5);
    assert(success);
    assert(il.getSize() == 2);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.head->data == 6);
    assert(il.tail->data == 7);
    assert(!il.remove(5));

    il.addFront(5);
    //remove back
    success = il.remove(7);
    assert(success);
    assert(il.getSize() == 2);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.head->data == 5);
    assert(il.tail->data == 6);
    assert(!il.remove(7));

    il.addBack(7);
    //remove middle
    success = il.remove(6);
    assert(success);
    assert(il.getSize() == 2);
    assert(il.head->next == il.tail);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
    assert(il.head->data == 5);
    assert(il.tail->data == 7);
    assert(!il.remove(6));

    //remove all
    il.remove(5);
    il.remove(7);
    assert(il.getSize() == 0);
    assert(il.head == NULL);
    assert(il.tail == NULL);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testAssign();
  t.testRemove();
  return EXIT_SUCCESS;
}


#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"
int main() {
  BstMap<int, int> m;
  m.add(2, 2);
  m.add(4, 3);
  m.add(1, 4);
  m.add(7, 5);
  m.add(9, 45);
  m.add(-1, 75);
  m.add(88, 52);
  m.add(17, 54);
  m.add(-23, 95);
  m.add(16, 4);
  m.add(44, 2);
  m.add(77, 1);

  //printf("%d\n", m.lookup(999));
  //2 4 1 7 3 9 -1 88 17 -23 16 44 77
  try {
    printf("%d\n", m.lookup(999));
    //code that might throw
  }
  catch (std::exception & e) {
    //code to handle a generic exception
    //delete m;
  }
  printf("%d\n", m.lookup(9));
  //m.remove(1);
  m.remove(9);
  m.remove(1);
  m.remove(88);
  m.printTree(m.getRoot());
  BstMap<int, int> m2;
  m2.add(4, 5);
  m2.add(2, 0);
  m2.add(1, 9);
  m2.add(5, 9);
  m2.add(9, 12);
  m2 = m;
  BstMap<int, int> m3(m);
  m2.printTree(m2.getRoot());
  m3.printTree(m3.getRoot());
  return EXIT_SUCCESS;
}

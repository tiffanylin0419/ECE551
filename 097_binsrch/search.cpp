#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //printf("%d %d\n", low, high);
  if (high - low <= 1) {
    return low;
  }
  int mid = (low + high) / 2;
  int m = f->invoke(mid);
  if (m == 0) {
    return mid;
  }
  else if (m > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, high);
  }
}

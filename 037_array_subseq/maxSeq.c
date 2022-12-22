#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * arr, size_t num) {
  size_t max_count = 0;
  size_t count = 0;
  if (num == 0) {
    return 0;
  }
  if (num > 0) {
    count++;
  }
  for (size_t i = 0; i < num - 1; i++) {
    if (arr[i] < arr[i + 1]) {
      count++;
    }
    else {
      if (count > max_count) {
        max_count = count;
      }
      count = 1;
    }
  }
  if (count > max_count) {
    max_count = count;
  }
  return max_count;
}

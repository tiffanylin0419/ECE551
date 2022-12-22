#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
size_t maxSeq_correct(int * arr, size_t num) {
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
void check(int arr[], size_t num) {
  if (maxSeq_correct(arr, num) != maxSeq(arr, num)) {
    exit(EXIT_FAILURE);
  }
}
int main() {
  //size_t num = 0;
  int arr[] = {-1, 1, 0, 0, 0, 0, 0, 2, 2147483647, 1, 3, 5, 7, 2, 4, 6, 9};
  check(arr, 0);
  check(arr, 1);
  check(arr, 2);
  check(arr, 3);
  check(arr, 4);
  check(arr, 17);

  return EXIT_SUCCESS;
}

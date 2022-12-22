#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = 1;
  for (unsigned i = 0; i < y; i++) {
    ans *= x;
  }
  printf("correct:%u, wrong:%u\n", ans, expected_ans);
  if (ans == expected_ans) {
    printf("1\n");
    return 1;
  }
  else {
    return 0;
  }
}

int main() {
  int n = 12;
  unsigned x[] = {-2, -2, 0, 1, 2, 3, 4, 5, 1, -1, 0, 2, 1, 0};
  unsigned y[] = {4, 1, 0, 1, 2, 3, 4, 5, 2, 2, 0, -1, 0, 8};

  for (int i = 0; i < n; i++) {
    printf("x=%u,y=%u\n", x[i], y[i]);
    if (run_check(x[i], y[i], power(x[i], y[i])) != 1) {
      printf("fail");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

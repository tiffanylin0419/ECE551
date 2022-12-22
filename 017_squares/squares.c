#include <stdbool.h>
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}

bool canprint(int x, int y, int x_1, int x_2, int y_1, int y_2) {
  if (y == y_1 || y == y_2 - 1) {
    if (x_1 <= x && x < x_2) {
      return true;
    }
  }
  if (x == x_1 || x == x_2 - 1) {
    if (y_1 <= y && y < y_2) {
      return true;
    }
  }
  return false;
}

bool inside(int x, int y, int s) {
  if (x < s && (y == 0 || y == s - 1)) {
    return true;
  }
  if (y < s && (x == 0 || x == s - 1)) {
    return true;
  }
  return false;
}
void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
      if (canprint(x, y, x_offset, x_offset + size2, y_offset, y_offset + size2)) {
        printf("*");
      }

      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
      else if (inside(x, y, size1)) {
        printf("#");
      }
      //else print a space
      else {
        printf(" ");
      }
      //when you finish counting x from 0 to w,
    }
    //print a newline
    printf("\n");
  }
}

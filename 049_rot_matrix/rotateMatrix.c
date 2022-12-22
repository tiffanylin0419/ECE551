#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 10
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Have %d arguments, supposed to have 2.\n", argc);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Non existance file.\n");
    return EXIT_FAILURE;
  }

  int matrix[LINE_SIZE][LINE_SIZE];
  //int rows = 0;
  //char line[LINE_SIZE][LINE_SIZE + 2];
  //int c;
  int count = 0;
  while ((matrix[count / 10][count % 10] = fgetc(f)) != EOF) {
    if (matrix[count / 10][count % 10] == 10) {
      if (count % 10 != 0) {
        fprintf(stderr, "Wrong number of columns.\n");
        return EXIT_FAILURE;
      }
      continue;
    }
    //printf("%c", c);
    count++;
  }
  if (count != 100) {
    fprintf(stderr, "wrong number of characters\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < LINE_SIZE; i++) {
    for (int j = 0; j < LINE_SIZE; j++) {
      printf("%c", matrix[LINE_SIZE - 1 - j][i]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

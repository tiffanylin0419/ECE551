#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortLine(FILE * f) {
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap = 0;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t k = 0; k < i; k++) {
    printf("%s", lines[k]);
    free(lines[k]);
  }
  free(lines);
  return;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLine(stdin);
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < argc; i++) {
    FILE * f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "Non existance file.\n");
      return EXIT_FAILURE;
    }
    sortLine(f);
    if (fclose(f) != 0) {
      printf("Cannot close file");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

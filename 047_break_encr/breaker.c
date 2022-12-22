#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int largest(int count[], int len) {
  int lar = 0;
  for (int i = 0; i < 26; i++) {
    if (count[lar] < count[i]) {
      lar = i;
    }
  }
  return (lar + 22) % 26;
}
void encrypt(FILE * f) {
  int c;
  int count[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      count[c - 'a']++;
    }
  }
  printf("%d\n", largest(count, 26));
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  encrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

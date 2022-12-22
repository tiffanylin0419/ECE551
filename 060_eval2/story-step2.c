#include "rand_story.h"
int main(int argc, char ** argv) {
  checkArgc(argc, 2);
  FILE * f = readFile(argv[1]);
  catarray_t * dict = init_catArr();
  //read line
  size_t sz = 0;
  char * line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    size_t colon = colonPos(line, dict, f);
    lineToDict(dict, line, colon);
  }
  printWords(dict);
  //free & close
  freeCatArr(dict);
  free(line);
  closeFile(f);
  return EXIT_SUCCESS;
}

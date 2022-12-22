#include "rand_story.h"
int main(int argc, char ** argv) {
  checkArgc(argc, 2);
  FILE * f = readFile(argv[1]);
  //read line
  size_t sz = 0;
  char * line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    change_Print(line, NULL, NULL, false, f);
  }
  //free & close
  free(line);
  closeFile(f);
  return EXIT_SUCCESS;
}

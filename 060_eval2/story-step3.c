#include "rand_story.h"
int main(int argc, char ** argv) {
  checkArgc(argc, 3);
  //dictoinary file
  catarray_t * dict = init_catArr();
  //read
  FILE * f = readFile(argv[1]);
  size_t sz = 0;
  char * line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    //find colon position & check error
    size_t colon = colonPos(line, dict, f);
    lineToDict(dict, line, colon);
  }
  //free & close
  free(line);
  closeFile(f);

  //story file
  f = readFile(argv[2]);
  category_t * used = init_cat();
  //read
  sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    change_Print(line, dict, used, false, f);
  }
  //free & close
  freeCat(used);
  freeCatArr(dict);
  free(line);
  closeFile(f);
  return EXIT_SUCCESS;
}

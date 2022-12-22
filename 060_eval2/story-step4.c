#include "rand_story.h"
int main(int argc, char ** argv) {
  int file_pos = 0;
  if (argc == 3) {
    file_pos = 0;
  }
  else if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Wrong argument option");
      return EXIT_FAILURE;
    }
    file_pos = 1;
  }
  else {
    checkArgc(0, 1);  //output error
  }
  //dictoinary file
  catarray_t * dict = init_catArr();
  //read
  FILE * f = readFile(argv[file_pos + 1]);
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
  f = readFile(argv[file_pos + 2]);
  category_t * used = init_cat();
  //read
  sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    change_Print(line, dict, used, file_pos == 1, f);
  }
  //free & close
  freeCat(used);
  freeCatArr(dict);
  free(line);
  closeFile(f);
  return EXIT_SUCCESS;
}

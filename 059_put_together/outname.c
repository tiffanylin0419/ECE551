#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  char * outName = malloc((len + 8) * sizeof(*outName));
  for (size_t i = 0; i < len; i++) {
    outName[i] = inputName[i];
  }
  char addName[7] = ".counts";
  for (size_t i = 0; i < 7; i++) {
    outName[len + i] = addName[i];
  }
  outName[len + 7] = '\0';
  return outName;
}

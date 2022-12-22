#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * answer = createCounts();
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "no file to open");
    exit(EXIT_FAILURE);
  }
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * good_line = malloc((strlen(line)) * sizeof(*good_line));
    for (size_t i = 0; i < strlen(line) - 1; i++) {
      good_line[i] = line[i];
    }
    good_line[strlen(line) - 1] = '\0';
    //printf("d%sd\n", good_line);
    addCount(answer, lookupValue(kvPairs, good_line));
    free(good_line);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "cannot close file");
    exit(EXIT_FAILURE);
  }
  return answer;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "not enough arguments");
    return EXIT_FAILURE;
  }
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argv[1] == NULL) {
    fprintf(stderr, "no filename");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    if (argv[i] == NULL) {
      fprintf(stderr, "no filename");
      return EXIT_FAILURE;
    }
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "no file");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "cannot close file");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}

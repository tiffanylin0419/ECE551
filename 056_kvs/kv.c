#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t readNum(FILE * f) {
  size_t count = 0;
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    count++;
  }
  free(line);
  return count;
}
kvpair_t * readAPair(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  kvpair_t * kvpair = malloc(sizeof(*kvpair));
  getline(&line, &sz, f);
  size_t eqPos = 0;
  for (size_t i = 0; i < sz; i++) {
    if (line[i] == '=') {
      eqPos = i;
      break;
    }
  }
  kvpair->Key = malloc((eqPos + 1) * sizeof(*kvpair->Key));
  for (size_t i = 0; i < eqPos; i++) {
    kvpair->Key[i] = line[i];
  }
  kvpair->Key[eqPos] = '\0';

  sz = strlen(line);
  kvpair->Value = malloc((sz - eqPos - 1) * sizeof(*kvpair->Value));
  //printf("sz: %ld,eq= %ld", sz, eqPos);
  for (size_t i = 0; i < sz - 2 - eqPos; i++) {
    kvpair->Value[i] = line[eqPos + 1 + i];
  }
  kvpair->Value[sz - 2 - eqPos] = '\0';
  free(line);
  return kvpair;
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot read file\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->Num = readNum(f);
  fclose(f);
  f = fopen(fname, "r");
  kvarray->Pairs = malloc(kvarray->Num * sizeof(*kvarray->Pairs));
  if (kvarray->Pairs == NULL) {
    fprintf(stderr, "Fail to malloc kvarray\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < kvarray->Num; i++) {
    kvarray->Pairs[i] = readAPair(f);
  }
  fclose(f);
  return kvarray;
}
void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->Num; i++) {
    free(pairs->Pairs[i]->Key);
    free(pairs->Pairs[i]->Value);
    free(pairs->Pairs[i]);
  }
  free(pairs->Pairs);
  free(pairs);
}

void printKV(kvpair_t * pair) {
  printf("key = '%s' value = '%s'\n", pair->Key, pair->Value);
}
void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->Num; i++) {
    printKV(pairs->Pairs[i]);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * value = NULL;
  for (size_t i = 0; i < pairs->Num; i++) {
    if (strcmp(pairs->Pairs[i]->Key, key) == 0) {
      value = pairs->Pairs[i]->Value;
      break;
    }
  }
  if (value == NULL) {
    return NULL;
  }
  return value;
}

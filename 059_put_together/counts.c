#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->len = 1;
  counts->one_count = malloc(sizeof(*counts->one_count));
  counts->one_count[0] = malloc(sizeof(*counts->one_count[0]));
  counts->one_count[0]->count = 0;
  counts->one_count[0]->value = NULL;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME}
  if (name == NULL) {
    c->one_count[0]->count++;
    return;
  }
  for (size_t i = 1; i < c->len; i++) {
    if (strcmp(c->one_count[i]->value, name) == 0) {
      c->one_count[i]->count++;
      return;
    }
  }
  c->len++;
  c->one_count = realloc(c->one_count, c->len * sizeof(*c->one_count));
  c->one_count[c->len - 1] = malloc(sizeof(*c->one_count[c->len - 1]));
  c->one_count[c->len - 1]->count = 1;
  c->one_count[c->len - 1]->value =
      malloc((strlen(name) + 1) * sizeof(*c->one_count[c->len - 1]->value));
  for (size_t i = 0; i < strlen(name); i++) {
    c->one_count[c->len - 1]->value[i] = name[i];
  }
  c->one_count[c->len - 1]->value[strlen(name)] = '\0';
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 1; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->one_count[i]->value, c->one_count[i]->count);
  }
  if (c->one_count[0]->count != 0) {
    fprintf(outFile, "<unknown> :%d", c->one_count[0]->count);
  }
  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->one_count[i]->value);
    free(c->one_count[i]);
  }
  free(c->one_count);
  free(c);
}

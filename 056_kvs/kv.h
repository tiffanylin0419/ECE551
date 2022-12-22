#ifndef __KV_H__
#define __KV_H__
#include <stdio.h>

struct _kvpair_t {
  //DEFINE ME!
  char * Key;
  char * Value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  //DEFINE ME!
  kvpair_t ** Pairs;
  size_t Num;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif

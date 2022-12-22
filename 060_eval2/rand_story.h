#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
void checkArgc(int argc, int val);
FILE * readFile(char * filename);
void closeFile(FILE * f);
bool isNum(char * category);
category_t * init_cat();
catarray_t * init_catArr();
void freeCat(category_t * cat);
void freeCatArr(catarray_t * catarr);
void freeAll(char * line,
             catarray_t * dict,
             category_t * used,
             char * category,
             FILE * f);
void wordBeUsed(const char * word, category_t * used);
category_t * catFromCatArr(char * category, catarray_t * dict);
bool notEmpty(char * category, category_t * used, catarray_t * dict);
void change_Print(char * line,
                  catarray_t * dict,
                  category_t * used,
                  bool different,
                  FILE * f);
size_t colonPos(char * line, catarray_t * dict, FILE * f);
void lineToDict(catarray_t * dict, char * line, size_t colon);
#endif

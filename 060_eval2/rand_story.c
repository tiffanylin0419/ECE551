#include "rand_story.h"
//check argument number
void checkArgc(int argc, int val) {
  if (argc != val) {
    fprintf(stderr, "wrong number of arguments");
    exit(EXIT_FAILURE);
  }
  return;
}
//open file and check error
FILE * readFile(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "file does not exist");
    exit(EXIT_FAILURE);
  }
  return f;
}
//close file and check error
void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    fprintf(stderr, "cannot close file");
    exit(EXIT_FAILURE);
  }
}
//check if string is number
bool isNum(char * category) {
  int num = atoi(category);
  for (size_t i = 1; i < strlen(category); i++) {
    num /= 10;
  }
  if (num > 0) {
    return true;
  }
  return false;
}
//get the last nth used word
const char * getWord(size_t num, category_t * used) {
  return used->words[used->n_words - num];
}
//initialize category
category_t * init_cat() {
  category_t * used = malloc(sizeof(*used));
  used->n_words = 0;
  used->name = NULL;
  used->words = NULL;
  return used;
}
//initialize category array
catarray_t * init_catArr() {
  catarray_t * dict = malloc(sizeof(*dict));
  dict->n = 0;
  dict->arr = NULL;
  return dict;
}

//free category
void freeCat(category_t * cat) {
  for (size_t i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
  free(cat);
  return;
}
//free category array
void freeCatArr(catarray_t * catarr) {
  for (size_t i = 0; i < catarr->n; i++) {
    for (size_t j = 0; j < catarr->arr[i].n_words; j++) {
      free(catarr->arr[i].words[j]);
    }
    free(catarr->arr[i].words);
    free(catarr->arr[i].name);
  }
  free(catarr->arr);
  free(catarr);
  return;
}
//free many things
void freeAll(char * line,
             catarray_t * dict,
             category_t * used,
             char * category,
             FILE * f) {
  if (used != NULL) {
    freeCat(used);
  }
  if (dict != NULL) {
    freeCatArr(dict);
  }
  free(category);
  free(line);
  closeFile(f);
  return;
}
//check if a word is used
bool wordUsed(char * word, category_t * used) {
  for (size_t i = 0; i < used->n_words; i++) {
    if (strcmp(word, used->words[i]) == 0) {
      return true;
    }
  }
  return false;
}
//add word into used word list
void wordBeUsed(const char * word, category_t * used) {
  if (used != NULL) {
    used->n_words++;
    used->words = realloc(used->words, sizeof(*used->words) * used->n_words);
    used->words[used->n_words - 1] = strdup(word);
  }
  return;
}
//get category from category array
category_t * catFromCatArr(char * category, catarray_t * dict) {
  for (size_t i = 0; i < dict->n; i++) {
    if (strcmp(category, dict->arr[i].name) == 0) {
      return &dict->arr[i];
    }
  }
  return NULL;
}
//check if the category is not all used already
bool notEmpty(char * category, category_t * used, catarray_t * dict) {
  category_t * cat = catFromCatArr(category, dict);
  for (size_t i = 0; i < cat->n_words; i++) {
    if (!wordUsed(cat->words[i], used)) {
      return true;
    }
  }
  return false;
}
//input one line and print the result after change
void change_Print(char * line,
                  catarray_t * dict,
                  category_t * used,
                  bool different,
                  FILE * f) {
  char * category = NULL;
  size_t category_size = 0;
  size_t i = 0;
  while (i < strlen(line)) {
    if (line[i] != '_') {
      printf("%c", line[i]);
    }
    else {
      i++;
      category = malloc(sizeof(*category));
      category_size = 0;
      while (i < strlen(line) && line[i] != '_') {
        category_size++;
        category = realloc(category, sizeof(*category) * (category_size + 1));
        category[category_size - 1] = line[i];
        if (i == strlen(line) - 1) {
          freeAll(line, dict, used, category, f);
          fprintf(stderr, "_does not match");
          exit(EXIT_FAILURE);
        }
        i++;
      }
      category[category_size] = '\0';
      //check if category is number
      const char * word = NULL;
      if (dict != NULL) {
        if (isNum(category)) {
          size_t getPos = atoi(category);
          if (getPos > used->n_words) {
            freeAll(line, dict, used, category, f);
            fprintf(stderr, "num too big");
            exit(EXIT_FAILURE);
          }
          word = getWord(getPos, used);  //get from used
        }
        else if (different == 0) {
          word = chooseWord(category, dict);
        }
        else {
          char * temp = NULL;
          if (notEmpty(category, used, dict)) {
            word = chooseWord(category, dict);
            temp = strdup(word);
            while (different && wordUsed(temp, used)) {
              word = chooseWord(category, dict);
              free(temp);
              temp = strdup(word);
            }
          }
          else {
            free(temp);
            freeAll(line, dict, used, category, f);
            fprintf(stderr, "no more unique word to use");
            exit(EXIT_FAILURE);
          }
          free(temp);
        }
      }
      else {
        word = "cat";
      }
      wordBeUsed(word, used);
      free(category);
      printf("%s", word);
    }
    i++;
  }
}
//find colon position & check error
size_t colonPos(char * line, catarray_t * dict, FILE * f) {
  size_t colon = 0;
  for (colon = 0; colon < strlen(line); colon++) {
    if (line[colon] == ':') {
      break;
    }
  }
  if (colon == strlen(line)) {
    freeCatArr(dict);
    free(line);
    fclose(f);
    fprintf(stderr, "no colon");
    exit(EXIT_FAILURE);
  }
  return colon;
}
//extract name from line
void lineToName(char * line, size_t colon, char * name) {
  for (size_t i = 0; i < colon; i++) {
    name[i] = line[i];
  }
  name[colon] = '\0';
  return;
}
//extract word from line
void lineToWord(char * line, size_t colon, char * word) {
  for (size_t i = 0; i < strlen(line) - colon - 1; i++) {
    if (line[i + colon + 1] == '\n') {
      word[i] = '\0';
      break;
    }
    word[i] = line[i + colon + 1];
  }
  return;
}
//save line to category array
void lineToDict(catarray_t * dict, char * line, size_t colon) {
  //line to name & word
  char * name = malloc(sizeof(*name) * (colon + 1));
  char * word = malloc(sizeof(*word) * (strlen(line) - colon));
  lineToName(line, colon, name);
  lineToWord(line, colon, word);

  bool contain = false;
  for (size_t i = 0; i < dict->n; i++) {
    if (strcmp(name, dict->arr[i].name) == 0) {
      contain = true;
      dict->arr[i].n_words++;
      dict->arr[i].words =
          realloc(dict->arr[i].words, dict->arr[i].n_words * sizeof(*dict->arr[i].words));
      dict->arr[i].words[dict->arr[i].n_words - 1] = word;
      free(name);
      break;
    }
  }
  if (!contain) {
    dict->n++;
    dict->arr = realloc(dict->arr, sizeof(*dict->arr) * dict->n);
    dict->arr[dict->n - 1].name = name;
    dict->arr[dict->n - 1].n_words = 1;
    dict->arr[dict->n - 1].words =
        malloc(sizeof(*dict->arr[dict->n - 1].words) * (dict->arr[dict->n - 1].n_words));
    dict->arr[dict->n - 1].words[0] = word;
  }
  return;
}

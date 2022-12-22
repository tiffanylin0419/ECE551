#include "pandemic.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
country_t parseLine(char * line) {
  //WRITE ME
  //no \0
  int largest[20] = {1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 5};
  size_t length = strlen(line);
  if (line[length - 1] != '\n') {
    length++;
  }
  if (length == 1) {
    fprintf(stderr, "Nothing in line\n");
    exit(EXIT_FAILURE);
  }
  unsigned comma = 0;
  size_t comma_pos = 0;
  for (size_t i = 0; i < length; i++) {
    if (line[i] == ',') {
      comma++;
      comma_pos = i;
      break;
    }
  }
  //line[length]='\0'
  //no ,
  if (comma == 0) {
    fprintf(stderr, "Cannot find comma\n");
    exit(EXIT_FAILURE);
  }
  if (comma_pos > 63) {
    fprintf(stderr, "Country Name Too Long\n");
    exit(EXIT_FAILURE);
  }
  //wrong type after ,
  if (comma_pos == length - 2) {
    fprintf(stderr, "Nothing after comma\n");
    exit(EXIT_FAILURE);
  }

  bool negative = false;
  size_t num_start = comma_pos + 1;
  while (num_start < length && (line[num_start] == ' ' || line[num_start] == '\t')) {
    num_start++;
  }
  if (line[num_start] == '-') {
    negative = true;
    num_start++;
  }
  //assign
  country_t ans;
  for (size_t i = 0; i < comma_pos; i++) {
    ans.name[i] = line[i];
  }
  ans.name[comma_pos] = '\0';

  bool all_zero = true;
  /*if (line[num_start] == '0') {
    no_zero = false;
  }*/
  for (size_t i = num_start; i < length - 1; i++) {
    if (line[i] != '0') {
      all_zero = false;
    }
  }
  if (all_zero) {
    ans.population = 0;
    return ans;
  }
  while (line[num_start] == '0') {
    num_start++;
  }

  if (length - num_start - 1 > 20) {
    fprintf(stderr, "Number too big\n");
    exit(EXIT_FAILURE);
  }
  if (length - num_start - 1 == 20) {
    for (int i = 0; i < 20; i++) {
      //printf( "%d %c %d %d\n", i, line[num_start + i], line[num_start + i] - '0', largest[i]);
      if (line[num_start + i] - '0' > largest[i]) {
        fprintf(stderr, "Number too big\n");
        exit(EXIT_FAILURE);
      }
      if (line[num_start + i] - '0' < largest[i]) {
        break;
      }
    }
  }
  //printf("%ld\n", length - num_start - 1);
  //printf("%d\n", largest[0]);
  //calculate
  if (isdigit(line[num_start]) == 0) {
    fprintf(stderr, "Not a number after comma");
    exit(EXIT_FAILURE);
  }

  uint64_t population = line[num_start] - '0';
  for (size_t i = num_start + 1; i < length - 1; i++) {
    if (isdigit(line[i]) != 0) {
      population = 10 * population + line[i] - '0';
    }
    else {
      break;
    }
  }

  ans.population = population;
  if (negative) {
    ans.population = (-1) * ans.population;
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days == 0) {
    avg[0] = 0;
    return;
  }
  if (n_days < 7) {
    double total = 0;
    for (size_t j = 0; j < n_days; j++) {
      total += data[j];
    }
    avg[0] = total / n_days;
    return;
  }
  for (size_t i = 0; i < n_days - 6; i++) {
    double total = 0;
    for (size_t j = 0; j < 7; j++) {
      total += data[i + j];
    }
    avg[i] = total / 7;
  }
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  unsigned cumulative = 0;
  for (size_t i = 0; i < n_days; i++) {
    cumulative += data[i];
    cum[i] = (double)cumulative / (pop / 100000);
  }
  return;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned number_cases = 0;
  size_t country = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > number_cases) {
        number_cases = data[i][j];
        country = i;
      }
    }
  }
  char * country_name = countries[country].name;
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
  return;
}

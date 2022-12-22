#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f(fname);
  if (!f) {
    std::cerr << "fail to open file" << fname << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * arr = new uint64_t[257]();
  char c;
  while (f.get(c)) {
    //std::cout << c;
    arr[(unsigned char)c]++;
  }
  arr[256] = 1;
  f.close();
  return arr;
}

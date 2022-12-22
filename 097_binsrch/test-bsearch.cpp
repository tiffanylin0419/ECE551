#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"
extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class LinearFunc : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int runtime;
  if (high > low) {
    runtime = log2(high - low) + 3;
  }
  else {
    runtime = 1;
  }
  CountedIntFn * func = new CountedIntFn(runtime, f, mesg);
  assert(binarySearchForZero(func, low, high) == expected_ans);
}

int main() {
  LinearFunc * func = new LinearFunc();
  SinFunction * sinfunc = new SinFunction();
  check(func, 2, 10, 2, "positive");
  check(func, -10, -1, -2, "negative");
  //check(func, -10, 10, 0, "neg&pos");
  check(func, -1, 1, 0, "neg&pos");
  check(func, -1, 4, 0, "neg&pos");
  check(func, 10, 10, 10, "low=high");
  check(func, 0, 0, 0, "low=high");
  check(func, -10, -10, -10, "low=high");

  check(func, -3, 0, -1, "exclude 0");
  check(func, 0, 7, 0, "include 0");

  check(sinfunc, 0, 150000, 52359, "sin");

  delete func;
  delete sinfunc;
  return (EXIT_SUCCESS);
}

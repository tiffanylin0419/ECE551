#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]), numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    numElements = rhs.numElements;
    //int * temp = new int[numElements];
    delete[] data;
    data = new int[numElements];
    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
    //numElements = rhs.numElements;
    //data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(0 <= index && index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(0 <= index && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (rhs.numElements != numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  int i;
  for (i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}

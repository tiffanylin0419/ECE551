#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
  int numRows, numColumns;
  //IntArray ** rows;
  vector<vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  //~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const vector<T> & operator[](int index) const;
  vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;

  template<typename X>
  friend ostream & operator<<(ostream & s, const Matrix<X> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {  //NULL
}
template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows.resize(r);
  for (typename vector<vector<T> >::iterator it = rows.begin(); it != rows.end(); ++it) {
    (*it).resize(c);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const vector<T> & Matrix<T>::operator[](int index) const {
  assert(0 <= index && index < numRows);
  return rows[index];
}

template<typename T>
vector<T> & Matrix<T>::operator[](int index) {
  assert(0 <= index && index < numRows);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows == rhs.numRows && numColumns == rhs.numColumns && rows == rhs.rows) {
    return true;
  }
  return false;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
  Matrix<T> ans(numRows, numColumns);
  //ans.rows = rows + rhs.rows;
  typename vector<vector<T> >::const_iterator it2 = rhs.rows.begin();
  typename vector<vector<T> >::const_iterator it1 = rows.begin();
  typename vector<vector<T> >::iterator it_ans = ans.rows.begin();

  while (it_ans != ans.rows.end()) {
    typename vector<T>::const_iterator itt2 = (*it2).begin();
    typename vector<T>::const_iterator itt1 = (*it1).begin();
    typename vector<T>::iterator itt_ans = (*it_ans).begin();
    while (itt_ans != (*it_ans).end()) {
      (*itt_ans) = (*itt1) + (*itt2);
      ++itt_ans;
      ++itt1;
      ++itt2;
    }
    ++it1;
    ++it2;
    ++it_ans;
  }
  return ans;
}

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (typename vector<vector<T> >::const_iterator it = rhs.rows.begin();
       it != rhs.rows.end();
       ++it) {
    //s << it;
    if (it != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";
    for (typename vector<T>::const_iterator itt = (*it).begin(); itt != (*it).end();
         ++itt) {
      if (itt != (*it).begin()) {
        s << ", ";
      }

      s << *itt;
    }
    s << "}";
  }
  s << " ]";
  return s;
}
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 protected:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << num;
    //std:: string str = ss.str();
    return ss.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  Expression *left, *right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    return "(" + left->toString() + " + " + right->toString() + ")";
  }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};

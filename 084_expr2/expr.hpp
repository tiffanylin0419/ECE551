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

class MathExpression : public Expression {
  Expression *left, *right;
  char op;

 public:
  MathExpression(char op, Expression * lhs, Expression * rhs) :
      left(lhs), right(rhs), op(op) {}
  virtual std::string toString() const {
    return "(" + left->toString() + " " + op + " " + right->toString() + ")";
  }
  virtual ~MathExpression() {
    delete left;
    delete right;
  }
};

class PlusExpression : public MathExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : MathExpression('+', lhs, rhs) {}
};

class MinusExpression : public MathExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : MathExpression('-', lhs, rhs) {}
};
class TimesExpression : public MathExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : MathExpression('*', lhs, rhs) {}
};
class DivExpression : public MathExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : MathExpression('/', lhs, rhs) {}
};

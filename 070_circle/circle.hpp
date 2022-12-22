
#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point c, double r) : center(c), radius(r) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

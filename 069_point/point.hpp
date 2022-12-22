#include <stdio.h>
#include <stdlib.h>

class Point {
  double x, y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

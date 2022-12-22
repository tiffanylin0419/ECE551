#include "point.hpp"

#include <cmath>
Point::Point() {
  x = 0;
  y = 0;
}
void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  return pow((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y), 0.5);
}

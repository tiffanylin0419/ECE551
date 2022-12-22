
#include "circle.hpp"

#include <algorithm>
#include <cmath>
using namespace std;

//Circle::Circle(Point c, double r) : center(c), radius(r) {}
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double r1 = max(radius, otherCircle.radius);
  double r2 = min(radius, otherCircle.radius);
  if (d > r2 + r1) {
    return 0;
  }
  if (d <= r1 - r2) {
    return M_PI * r2 * r2;
  }
  double d1 = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
  double d2 = d - d1;
  double A2 = r2 * r2 * acos(d2 / r2) - d2 * pow(r2 * r2 - d2 * d2, 0.5);
  double A1 = r1 * r1 * acos(d1 / r1) - d1 * pow(r1 * r1 - d1 * d1, 0.5);
  return A1 + A2;
}

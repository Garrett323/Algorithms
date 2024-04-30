#include "primitives.hpp"
#include <math.h>

Point::Point(int x, int y) : x(x), y(y) {}
Point::Point() : x(0), y(0) {}

Point Point::operator+(const Point &rhs) const {
  return {x + rhs.x, y + rhs.y};
}

Point Point::operator-(const Point &rhs) const {
  return {x - rhs.x, y - rhs.y};
}

Point &Point::operator+=(const Point &rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
}
Point &Point::operator*=(const int &scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Point Point::operator*(const int &scalar) const {
  return {x * scalar, y * scalar};
}

std::ostream &operator<<(std::ostream &stream, const Point &p) {
  stream << std::format("[x: {}, y: {}]", p.x, p.y);
  return stream;
}

bool Point::operator==(const Point &rhs) const {
  return x == rhs.x && y == rhs.y;
}

void Point::print(void) { std::cout << "x: " << x << ",y: " << y << "\n"; }

float Point::norm(void) { return sqrt(x * x + y * y); }
int Point::squared_norm(void) { return x * x + y * y; }

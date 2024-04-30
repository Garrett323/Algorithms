#pragma once
#include <format>
#include <iostream>

class Point {
public:
  int x;
  int y;
  Point(int x, int y);
  Point();
  Point operator+(const Point &rhs) const;
  Point operator-(const Point &rhs) const;
  Point &operator+=(const Point &rhs);
  Point &operator*=(const int &scalar);
  Point operator*(const int &scalar) const;
  bool operator==(const Point &rhs) const;
  void print(void);
  float norm(void);
  int squared_norm(void);
};

std::ostream &operator<<(std::ostream &, const Point &);

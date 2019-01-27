//
// Created by 79776 on 26.01.2019.
//

#ifndef METHODSOFOPTIMIZATION_POINT_H
#define METHODSOFOPTIMIZATION_POINT_H

#include <cmath>

struct Point {
public:
    double x, y;

    Point(): x(0.0), y(0.0) {};
    Point(double x, double y): x(x), y(y) {};
    Point(double val): x(val), y(val) {};
    Point(int x, int y): x(static_cast<double>(x)), y(static_cast<double>(y)) {};
    Point(int val): x(static_cast<double>(val)), y(static_cast<double>(val)) {};

    Point operator + (Point p) { return Point(x + p.x, y + p.y); }
    Point operator - (Point p) { return Point(x - p.x, y - p.y); }

    Point operator * (double num) { return Point(x * num, y * num); }

    static double norm(Point p) { return std::max(fabs(p.x), fabs(p.y)); }

};

#endif //METHODSOFOPTIMIZATION_POINT_H

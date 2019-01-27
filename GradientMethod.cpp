//
// Created by rustam on 10.01.19.
//

#include <cmath>
#include "GradientMethod.h"

GradientMethod::GradientMethod(double xBegin, double yBegin, double lambda, double eps, FuncType&& func):
                                Method(std::move(func), Point(xBegin, yBegin), eps), lambda(lambda) {}

GradientMethod::GradientMethod(Point pBegin, double lambda, double eps, FuncType&& func):
        Method(std::move(func), Point(pBegin), eps), lambda(lambda) {}

void GradientMethod::init(Point pBegin, double lambda, double eps, double (*func) (Point)) {
    this->pBegin.x = pBegin.x;
    this->pBegin.y = pBegin.y;
    this->lambda = lambda;
    this->eps = eps;
    this->func = func;
    this->iterationsNumber = 0;
    this->result = 0.0f;
}

Point GradientMethod::solve() {
    Point pCur = Point(INT32_MAX), pNext = pBegin;
    while (Point::norm(pNext - pCur) > eps) {
        pCur = pNext;
        pNext = pCur - gradFunc(pCur) * lambda;
        if (func(pNext) > func(pCur)) {
            lambda /= 2;
            pNext = pCur;
            pCur = Point(INT32_MAX);
            continue;
        }
        iterationsNumber++;
        stepVec.push_back(pNext);
    }
    result = pNext;
    return result;
}

Point GradientMethod::gradFunc(Point p) {
    double dx = 1e-6;
    double dy = 1e-6;
    double dzdx = ( func(Point(p.x + dx, p.y)) - func(Point(p.x, p.y)) ) / dx;
    double dzdy = ( func(Point(p.x, p.y + dy)) - func(Point(p.x, p.y)) ) / dy;
    return Point(dzdx, dzdy);
}

void GradientMethod::reset() {
    iterationsNumber = 0;
    result = Point(0.0f, 0.0f);
    stepVec.clear();
}

double GradientMethod::getLambda() const {
    return lambda;
}

void GradientMethod::setLambda(double lambda) {
    this->lambda = lambda;
}

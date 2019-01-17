//
// Created by rustam on 10.01.19.
//

#include <cmath>
#include "GradientMethod.h"

GradientMethod::GradientMethod(double xBegin, double lambda, double eps, FuncType&& func):
                                Method(std::move(func), xBegin, eps), lambda(lambda) {}

void GradientMethod::init(double xBegin, double lambda, double eps, double (*func) (double)) {
    this->xBegin = xBegin;
    this->lambda = lambda;
    this->eps = eps;
    this->func = func;
    this->iterationsNumber = 0;
    this->result = 0.0f;
}

double GradientMethod::solve() {
    double xCur, xNext = xBegin;
    xVector.push_back(xBegin);
    do {
        iterationsNumber++;
        xCur = xNext;
        xNext = xCur - lambda * gradFunc(xCur);
        xVector.push_back(xNext);
    } while (fabs(xNext - xCur) > eps);
    result = xNext;
    return result;
}

double GradientMethod::gradFunc(double x) {
    double dx = 1e-6;
    return (func(x + dx) - func(x)) / dx;
}

void GradientMethod::reset() {
    iterationsNumber = 0;
    result = 0;
    xVector.clear();
}

double GradientMethod::getLambda() const {
    return lambda;
}

void GradientMethod::setLambda(double lambda) {
    this->lambda = lambda;
}

//
// Created by rustam on 10.01.19.
//

#include <cmath>
#include "GradientMethod.h"

GradientMethod::GradientMethod(double xBegin, double lambda, double eps, double (*func) (double)):
                                xBegin(xBegin), eps(eps), lambda(lambda), func(func) {
    xVector.push_back(xBegin);
    iterationsNumber = 0;
}

void GradientMethod::init(double xBegin, double lambda, double eps, double (*func) (double)) {
    this->xBegin = xBegin;
    this->lambda = lambda;
    this->eps = eps;
    this->func = func;
    this->iterationsNumber = 0;
}

std::vector<double> GradientMethod::solve() {
    double xCur, xNext = xBegin;
    do {
        iterationsNumber++;
        xCur = xNext;
        xNext = xCur - lambda * gradFunc(xCur);
        xVector.push_back(xNext);
    } while (fabs(xNext - xCur) > eps);

    return xVector;
}

double GradientMethod::gradFunc(double x) {
    double dx = 1e-6;
    return (func(x + dx) - func(x)) / dx;
}

void GradientMethod::reset() {
    xBegin = eps = lambda = 0.0f;
    iterationsNumber = 0;
    xVector.clear();
}

double GradientMethod::getXBegin() const {
    return xBegin;
}

void GradientMethod::setXBegin(double xBegin) {
    GradientMethod::xBegin = xBegin;
}

double GradientMethod::getEps() const {
    return eps;
}

void GradientMethod::setEps(double eps) {
    GradientMethod::eps = eps;
}

double GradientMethod::getLambda() const {
    return lambda;
}

void GradientMethod::setLambda(double lambda) {
    GradientMethod::lambda = lambda;
}

const std::vector<double> &GradientMethod::getXVector() const {
    return xVector;
}

unsigned GradientMethod::getIterationsNumber() const {
    return iterationsNumber;
}

double GradientMethod::getXMin() const {
    return xVector.back();
}

const FuncPointer& GradientMethod::getFunc() const {
    return func;
}

void GradientMethod::setFunc(const FuncPointer &func) {
    this->func = func;
}

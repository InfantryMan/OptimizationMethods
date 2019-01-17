//
// Created by rustam on 15.01.19.
//

#include "Method.h"

double Method::getXBegin() const {
    return this->xBegin;
}

void Method::setXBegin(double xBegin) {
    this->xBegin = xBegin;
}

double Method::getEps() const {
    return this->eps;
}

void Method::setEps(double eps) {
    this->eps = eps;
}

const FuncType & Method::getFunc() const {
    return func;
}

void Method::setFunc(const FuncType &func) {
    this->func = func;
}

const std::vector<double> & Method::getXVector() const {
    return xVector;
}

unsigned Method::getIterationsNumber() const {
    return iterationsNumber;
}

double Method::getResult() const {
    return result;
}

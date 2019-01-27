//
// Created by rustam on 15.01.19.
//

#include "Method.h"

Point Method::getPBegin() const {
    return this->pBegin;
}

void Method::setPBegin(Point pBegin) {
    this->pBegin = pBegin;
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

const std::vector<Point> & Method::getStepVec() const {
    return stepVec;
}

unsigned Method::getIterationsNumber() const {
    return iterationsNumber;
}

Point Method::getResult() const {
    return result;
}

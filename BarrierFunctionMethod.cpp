//
// Created by rustam on 15.01.19.
//

#include <cmath>
#include <functional>
#include "BarrierFunctionMethod.h"
#include "GradientMethod.h"

BarrierFunctionMethod::BarrierFunctionMethod() {}

BarrierFunctionMethod::BarrierFunctionMethod(Point pBegin, double rkBegin, double eps, double C, FuncType&& func, double bound, bool isLeft):
    Method(std::move(func), pBegin, eps), rkBegin(rkBegin), rk(rkBegin), C(C), bound(bound), isLeft(isLeft) {}

double BarrierFunctionMethod::getRkBegin() const {
    return rkBegin;
}

void BarrierFunctionMethod::setIsLeft(bool isLeft) {
    this->isLeft = isLeft;
}

void BarrierFunctionMethod::setBound(double bound) {
    this->bound = bound;
}

double BarrierFunctionMethod::getC() const {
    return C;
}

void BarrierFunctionMethod::setC(double C) {
    this->C = C;
}

const std::vector<double> & BarrierFunctionMethod::getRkVector()  const {
    return rkVector;
}

void BarrierFunctionMethod::setRk(double rk) {
    this->rk = rk;
}


const FuncType & BarrierFunctionMethod::getF() const {
    return F;
}

//void BarrierFunctionMethod::setF(const FuncType &f) {
//    this->F = f;
//}
//
//const FuncType & BarrierFunctionMethod::getP() const {
//    return P;
//}
//
//void BarrierFunctionMethod::setP(const FuncType &f) {
//    this-> P = f;
//}
//
//double BarrierFunctionMethod::F(Point p) {
//    return func(p) + P(p);
//}
//
//double BarrierFunctionMethod::P(double x) {
//    return isLeft? - rk * 1 / (x - bound) : rk * 1 / (x - bound);
//}
//
//bool BarrierFunctionMethod::isInsideBound(double x) {
//    if (isLeft)
//        if (x <= bound)
//            return true;
//    if (!isLeft)
//        if (x >= bound)
//            return true;
//    return false;
//}
//
//bool BarrierFunctionMethod::isMethodEnd(double x) {
//    double res = P(x);
//    return fabs(res) <= eps;
//}
//

Point BarrierFunctionMethod::solve() {
    Point p = pBegin;
    const double epsGradientMethod = 1e-3;
    bool isInside;
    const unsigned gradientMethodIterationsMax = 10;
    unsigned gradientMethodIterationsCurrent = 1;

    GradientMethod gradientMethod(pBegin, epsGradientMethod, [this](Point p) { return F(p); });

//    while (true) {
//        gradientMethod.setPBegin(p);
//        p = gradientMethod.solve();
//        isInside = isInsideBound(p);
//        gradientMethodIterationsCurrent = 1;
//
//        stepVec.push_back(p);
//        rkVector.push_back(rk);
//
//        if (isMethodEnd(p)) {
//            break;
//        }
//
//        rk /= C;
//        iterationsNumber++;
//        gradientMethod.reset();
//    }

    result = p;
    return result;
}

void BarrierFunctionMethod::setBoundFunc(const FuncType &f) {
    this->boundFunc = f;
}


//Point BarrierFunctionMethod::solve() {
//    return Point(228,228);
//}
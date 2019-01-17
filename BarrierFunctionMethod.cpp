//
// Created by rustam on 15.01.19.
//

#include <cmath>
#include <functional>
#include "BarrierFunctionMethod.h"
#include "GradientMethod.h"

BarrierFunctionMethod::BarrierFunctionMethod(double xBegin, double rkBegin, double eps, double C, FuncType&& func, double bound, bool isLeft = true):
    Method(std::move(func), xBegin, eps), rkBegin(rkBegin), rk(rkBegin), C(C), bound(bound), isLeft(isLeft) {}

double BarrierFunctionMethod::getRkBegin() const {
    return rkBegin;
}

double BarrierFunctionMethod::getC() const {
    return C;
}

const std::vector<double> & BarrierFunctionMethod::getRkVector()  const {
    return rkVector;
}

void BarrierFunctionMethod::setRk(double rk) {
    this->rk = rk;
}

const FuncType & BarrierFunctionMethod::getF() const {


}

double BarrierFunctionMethod::F(double x) {
    return func(x) + P(x);
}

double BarrierFunctionMethod::P(double x) {
    return isLeft? - rk * 1 / (x - bound) : rk * 1 / (x - bound);
}

bool BarrierFunctionMethod::isInsideBound(double x) {
    if (isLeft)
        if (x <= bound)
            return true;
    if (!isLeft)
        if (x >= bound)
            return true;
    return false;
}

bool BarrierFunctionMethod::isMethodEnd(double x) {
    double res = P(x);
    return fabs(res) <= eps;
}

double BarrierFunctionMethod::solve() {
    double x = xBegin;
    double lambdaGradientMethod = 0.1;
    const double epsGradientMethod = 1e-3;
    bool isInside;
    const unsigned gradientMethodIterationsMax = 10;
    unsigned gradientMethodIterationsCurrent = 1;

    GradientMethod gradientMethod(xBegin, lambdaGradientMethod, epsGradientMethod, [this](double x) { return F(x); });

    while (true) {
        gradientMethod.setXBegin(x);
        x = gradientMethod.solve();
        isInside = isInsideBound(x);
        gradientMethodIterationsCurrent = 1;

        while (!isInside) {
            if (gradientMethodIterationsCurrent >= gradientMethodIterationsMax) {
                std::cerr << "Градиентный метод не даёт ответ в пределах ограничений" << std::endl;
                return -1;
            }

            lambdaGradientMethod /= 2;
            gradientMethod.reset();
            gradientMethod.setLambda(lambdaGradientMethod);
            x = gradientMethod.solve();
            isInside = isInsideBound(x);
            gradientMethodIterationsCurrent++;
        }
        xVector.push_back(x);
        rkVector.push_back(rk);

        if (isMethodEnd(x)) {
            break;
        }

        rk /= C;
        iterationsNumber++;
        gradientMethod.reset();
    }

    result = x;
    return result;
}
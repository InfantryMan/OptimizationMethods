//
// Created by rustam on 15.01.19.
//

#ifndef METHODSOFOPTIMIZATION_BARRIERFUNCTIONMETHOD_H
#define METHODSOFOPTIMIZATION_BARRIERFUNCTIONMETHOD_H


#include "Method.h"

class BarrierFunctionMethod: public Method {
private:
    std::vector<double> rkVector;
    double rkBegin, rk, C, bound;
    bool isLeft;
    double F(double x);
    double P(double x);
    bool isInsideBound(double x);
    bool isMethodEnd(double x);
public:
    BarrierFunctionMethod(double xBegin, double rkBegin, double eps, double C, FuncType&& func, double bound, bool isLeft);

    Point solve() override;

    double getRkBegin() const;
    double getC() const;
    const std::vector<double> & getRkVector() const;
    void setRk(double rk);
    const FuncType & getF() const;
};

#endif //METHODSOFOPTIMIZATION_BARRIERFUNCTIONMETHOD_H

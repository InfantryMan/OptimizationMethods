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
    FuncType F;
    FuncType P;

    FuncType boundFunc;

    bool isInsideBound(Point p);
    bool isMethodEnd(Point p);
public:
    BarrierFunctionMethod();
    BarrierFunctionMethod(Point pBegin, double rkBegin, double eps, double C, FuncType&& func, double bound, bool isLeft);

    Point solve() override;

    double getRkBegin() const;
    void setC(double C);
    double getC() const;
    void setBound(double bound);
    void setIsLeft(bool isLeft);
    const std::vector<double> & getRkVector() const;
    void setRk(double rk);
    const FuncType & getF() const;

    void setBoundFunc(const FuncType &f);

//    const FuncType & getF() const;
//    void setF(const FuncType &f);
//
//    const FuncType & getP() const;
//    void setP(const FuncType &f);
};

#endif //METHODSOFOPTIMIZATION_BARRIERFUNCTIONMETHOD_H

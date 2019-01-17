//
// Created by rustam on 10.01.19.
//

#ifndef METHODSOFOPTIMIZATION_GRADIENTMETHOD_H
#define METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

#include <iostream>
#include <vector>
#include <functional>
#include "Method.h"

class GradientMethod: public Method {
private:
    double lambda;
    double gradFunc(double x);
public:
    GradientMethod(double xBegin, double lambda, double eps, FuncType&& func);

    double solve() override;

    double getLambda() const;
    void setLambda(double lambda);

    void init(double xBegin, double lambda, double eps, double (*func) (double x));
    void reset();

};

#endif //METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

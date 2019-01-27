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
    Point gradFunc(Point p);
public:
    GradientMethod(double xBegin, double yBegin, double lambda, double eps, FuncType&& func);
    GradientMethod(Point pBegin, double lambda, double eps, FuncType&& func);

    Point solve() override;

    double getLambda() const;
    void setLambda(double lambda);

    void init(Point pBegin, double lambda, double eps, double (*func) (Point p));
    void reset();

};

#endif //METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

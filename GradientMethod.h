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
    Point gradFunc(Point p);
    Point nextPoint(Point pCur, double lamb);
    double lExtrCalc(std::vector<std::pair<double, double>> & fl);
    double lambdaCalc(Point pCur);
public:
    GradientMethod();
    GradientMethod(double xBegin, double yBegin, double eps, FuncType&& func);
    GradientMethod(Point pBegin, double eps, FuncType&& func);

    Point solve() override;

    void init(Point pBegin, double eps, double (*func) (Point p));
    void reset();

};

#endif //METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

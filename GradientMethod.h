//
// Created by rustam on 10.01.19.
//

#ifndef METHODSOFOPTIMIZATION_GRADIENTMETHOD_H
#define METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

#include <iostream>
#include <vector>

using FuncPointer = double(*)(double);

class GradientMethod {
private:
    double xBegin, eps, lambda;
    unsigned iterationsNumber;
    std::vector<double> xVector;
public:
    double getXBegin() const;
    void setXBegin(double xBegin);
    double getEps() const;
    void setEps(double eps);
    double getLambda() const;
    void setLambda(double lambda);
    const std::vector<double> &getXVector() const;
    unsigned getIterationsNumber() const;
    const FuncPointer& getFunc() const;
    void setFunc(const FuncPointer& func);
private:
    FuncPointer func;
    double gradFunc(double x);
public:
    GradientMethod(double xBegin, double lambda, double eps, double (*func) (double x));
    void init(double xBegin, double lambda, double eps, double (*func) (double x));
    std::vector<double> solve();
    void reset();
    double getXMin() const;
};


#endif //METHODSOFOPTIMIZATION_GRADIENTMETHOD_H

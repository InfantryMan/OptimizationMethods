//
// Created by rustam on 11.01.19.
//

#ifndef METHODSOFOPTIMIZATION_METHOD_H
#define METHODSOFOPTIMIZATION_METHOD_H

#include <iostream>
#include <vector>
#include <functional>
#include "Point.h"

// Новый тип - функтор для функций типа: double (Point)
using FuncType = std::function<double (Point)>;

// Определение класса "Метод"
class Method {
protected:
    FuncType func;      // указатель на оптимизируемую функцию
    Point pBegin;      // начальное приближение по X и Y
    double eps;         // необходимая точность
    int iterationsNumber;      // произведённое количество итераций при поиске минимума
    std::vector<Point> stepVec;    // вектор шагов по X и Y
    Point result;      // полученный Xmin, Ymin

public:
    // Конструкторы
    Method(): func(nullptr), pBegin(0.0f, 0.0f), eps(0.0f), iterationsNumber(0), result(0.0f) {}
    Method(FuncType&& f, Point pBegin, double eps): func(f), pBegin(pBegin), eps(eps), iterationsNumber(0), result(0.0f) {}

    // Решатель задачи оптимизации
    virtual Point solve() = 0;

    // Геттеры и сеттеры
    Point getPBegin() const;
    void setPBegin(Point pBegin);

    double getEps() const;
    void setEps(double eps);

    const FuncType & getFunc() const;
    void setFunc(const FuncType &func);

    const std::vector<Point> & getStepVec() const;

    unsigned getIterationsNumber() const;

    Point getResult() const;
};

#endif //METHODSOFOPTIMIZATION_METHOD_H

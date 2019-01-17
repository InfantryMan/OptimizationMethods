//
// Created by rustam on 11.01.19.
//

#ifndef METHODSOFOPTIMIZATION_METHOD_H
#define METHODSOFOPTIMIZATION_METHOD_H

#include <iostream>
#include <vector>
#include <functional>

// Новый тип - функтор для функций типа: double (double)
using FuncType = std::function<double (double)>;

// Определение класса "Метод"
class Method {
protected:
    FuncType func;      // указатель на оптимизируемую функцию
    double xBegin;      // начальное приближение
    double eps;         // необходимая точность
    unsigned iterationsNumber;      // произведённое количество итераций при поиске минимума
    std::vector<double> xVector;    // вектор шагов по X
    double result;      // полученный xmin

public:
    // Конструкторы
    Method(): func(nullptr), xBegin(0.0f), eps(0.0f), iterationsNumber(0), result(0.0f) {}
    Method(FuncType&& f, double xBegin, double eps): func(f), xBegin(xBegin), eps(eps), iterationsNumber(0), result(0.0f) {}

    // Решатель задачи оптимизации
    virtual double solve() = 0;

    // Геттеры и сеттеры
    double getXBegin() const;
    void setXBegin(double xBegin);

    double getEps() const;
    void setEps(double eps);

    const FuncType & getFunc() const;
    void setFunc(const FuncType &func);

    const std::vector<double> & getXVector() const;

    unsigned getIterationsNumber() const;

    double getResult() const;
};

#endif //METHODSOFOPTIMIZATION_METHOD_H

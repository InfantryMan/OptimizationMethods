//
// Created by rustam on 10.01.19.
//

#include <cmath>
#include "GradientMethod.h"

GradientMethod::GradientMethod() {}

GradientMethod::GradientMethod(double xBegin, double yBegin, double eps, FuncType&& func):
                                Method(std::move(func), Point(xBegin, yBegin), eps) {}

GradientMethod::GradientMethod(Point pBegin, double eps, FuncType&& func):
        Method(std::move(func), Point(pBegin), eps) {}

void GradientMethod::init(Point pBegin, double eps, double (*func) (Point)) {
    this->pBegin.x = pBegin.x;
    this->pBegin.y = pBegin.y;
    this->eps = eps;
    this->func = func;
    this->iterationsNumber = 0;
    this->result = 0.0f;
}

double GradientMethod::lambdaCalc(Point pCur) {
    double dl = 0.005;
    double eps1 = 0.001, eps2 = 0.01;
    double l1 = 0.01;
    double lRes;

    while (true) {
        double l2 = l1 + dl;
        double l3;

        //
        Point npl1 = nextPoint(pCur, l1);

        double f1 = func(nextPoint(pCur, l1));
        double f2 = func(nextPoint(pCur, l2));

        if (f1 > f2) {
            l3 = l1 + 2 * dl;
        } else {
            l3 = l1 - dl;
        }

        double f3 = func(nextPoint(pCur, l3));

        first:
        std::vector<std::pair<double, double>> fl = {
                {f1, l1},
                {f2, l2},
                {f3, l3}
        };

        std::vector<double> fs = {f1, f2, f3};
        double fMin = *std::min_element(fs.begin(), fs.end());

        double lMin;
        for (auto &i : fl) {
            if (i.first == fMin) {
                lMin = i.second;
                break;
            }
        }

        double lExtr = lExtrCalc(fl);
        double fExtr = func(nextPoint(pCur, lExtr));

        //
        double e1 = fabs((fMin - fExtr) / fExtr);
        if (fExtr < 1e-15) {
            e1 = fabs(fMin - fExtr);
        }
        double e2 = fabs((lMin - lExtr) / lExtr);
        if (lExtr < 1e-15) {
            e2 = fabs(lMin - lExtr);
        }

        if (e1 < eps1 && e2 < eps2) {
            lRes = lExtr;
            break;
        }

        std::vector<double> ls = {l1, l2, l3};
        double lLeft = *std::min_element(ls.begin(), ls.end());
        double lRight = *std::max_element(ls.begin(), ls.end());

        if (lExtr >= lLeft && lExtr <= lRight) {
            double l2Copy = l2;
            if (fMin > fExtr) {
                l2 = lExtr;
                if (l2 > l2Copy) {
                    l1 = l2Copy;
                } else {
                    l3 = l2Copy;
                }
            } else {
                l1 = lMin;
                dl /= 2;
                continue;
            }
            f1 = func(nextPoint(pCur, l1));
            f2 = func(nextPoint(pCur, l2));
            f3 = func(nextPoint(pCur, l3));
            goto first;
        } else {
            l1 = lExtr;
        }
    }
    return lRes;
}

Point GradientMethod::solve() {
    Point pCur = Point(INT32_MAX), pNext = pBegin;
    double lambda;

    while (Point::norm(pNext - pCur) > eps) {
        pCur = pNext;
        stepVec.push_back(pNext);
        lambda = lambdaCalc(pCur);
        pNext = pCur - gradFunc(pCur) * lambda;
        iterationsNumber++;
    }
    result = pNext;
    return result;
}

Point GradientMethod::nextPoint(Point pCur, double lamb) {
    return pCur - gradFunc(pCur) * lamb;
}

Point GradientMethod::gradFunc(Point p) {
    double dx = 1e-6;
    double dy = 1e-6;
    double dzdx = ( func(Point(p.x + dx, p.y)) - func(Point(p.x, p.y)) ) / dx;
    double dzdy = ( func(Point(p.x, p.y + dy)) - func(Point(p.x, p.y)) ) / dy;
    return Point(dzdx, dzdy);
}

void GradientMethod::reset() {
    iterationsNumber = 0;
    result = Point(0.0f, 0.0f);
    stepVec.clear();
}

double GradientMethod::lExtrCalc(std::vector<std::pair<double, double>> & fl) {
    return (
                (pow(fl[1].second, 2) - pow(fl[2].second, 2)) * fl[0].first +
                (pow(fl[2].second, 2) - pow(fl[0].second, 2)) * fl[1].first +
                (pow(fl[0].second, 2) - pow(fl[1].second, 2)) * fl[2].first
           ) / (
                (fl[1].second - fl[2].second) * fl[0].first +
                (fl[2].second - fl[0].second) * fl[1].first +
                (fl[0].second - fl[1].second) * fl[2].first
           ) * 0.5;
}
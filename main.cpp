#include <iostream>
#include "GradientMethod.h"
#include "Gnuplot.h"
#include "BarrierFunctionMethod.h"
#include "Point.h"

double f(Point p) {
    return p.x * p.x + p.y;
}

namespace Grad {
    const Point pBegin(-10.0f, -10.0f);
    const double lambda = 10, eps = 1e-3;
    const char *fileName = "gradient_result.txt";
}

namespace Barr {
    const Point pBegin(-10.0f, -10.0f);
    double rk = 10.0f, C = 2.0f, eps = 1e-2, bound = 1.0f;
    bool isLeft = true;
    const char *fileName = "barrier_result.txt";
}

void printMethodResultToTerminal(const Method *method, const std::string & methodName, const std::string & funcAsString, const std::string & description = "", bool verbosity = false) {
    std::cout << "\t\t" << methodName << " method for " << funcAsString << std::endl;
    std::cout << "xBegin = " << method->getPBegin().x << " " << "yBegin = " << method->getPBegin().y << "; eps = " << method->getEps() << std::endl;
    std::cout << description << std::endl;
    if (verbosity) {
        Point p;
        std::cout << "i\tx\ty\tf" << std::endl;
        for (unsigned i = 0; i < method->getStepVec().size(); i++) {
            p = Point(method->getStepVec()[i].x, method->getStepVec()[i].y);
            std::cout << i << "\t" << method->getStepVec()[i].x << "\t" << method->getStepVec()[i].y << "\t" << f(p) << std::endl;
        }
    }
    std::cout << "Number of iterations = " << method->getIterationsNumber() << std::endl;
    std::cout << "xMin = " << method->getResult().x << " " << "yMin = " << method->getResult().y << std::endl;
    std::cout << "f(xMin, yMin) = " << f(method->getResult()) << std::endl;
}

void printMethodResultToFile(const Method *method, const char * fileName) {
    FILE *fp = fopen(fileName, "w");

    if (fp == nullptr) {
        std::cerr << "Can not open file " << fileName << std::endl;
        return;
    }

    const std::vector<Point> & result = method->getStepVec();
    const FuncType & f = method->getFunc();

    for (Point point : result) {
        fprintf(fp, "%lf %lf %lf\n", point.x, point.y, f(point));
    }

    fclose(fp);
}


int main() {
    auto *gradientMethod = new GradientMethod(Grad::pBegin, Grad::lambda, Grad::eps, f);
    gradientMethod->solve();
    const std::string gradDescr = "lambda = " + std::to_string(Grad::lambda);

    printMethodResultToTerminal(gradientMethod, "Gradient", "z = x * x + y * y", gradDescr, true);
    printMethodResultToFile(gradientMethod, Grad::fileName);

    Gnuplot plotGradient;
    plotGradient.setTitle("Gradient method");
    plotGradient.setxLabel("x");
    plotGradient.setyLabel("y");
    plotGradient.setGrid(true);
    plotGradient.setxRange(Grad::pBegin.x, -Grad::pBegin.x);
    plotGradient.setyRange(Grad::pBegin.y, -Grad::pBegin.y);

    plotGradient.setLineStyle(1, Color::GREEN, 1, 1.5);
    plotGradient.setLineStyle(2, Color::RED, 1, 1.5, 2, 1.0);
    plotGradient("splot x * x + y * y with lines linestyle 1, 'gradient_result.txt' with linespoints linestyle 2");

//    auto *barrierFunctionMethod = new BarrierFunctionMethod(Barr::xBegin, Barr::rk, Barr::eps, Barr::C, f, Barr::bound, Barr::isLeft);
//    barrierFunctionMethod->solve();
//    const std::string barrDescr = std::string("x ") + std::string(Barr::isLeft ? "<=" : ">=") + std::to_string(Barr::bound);
//
//
//    printMethodResultToTerminal(barrierFunctionMethod, "Barrier function", "y = x * x", barrDescr, true);
//    printMethodResultToFile(barrierFunctionMethod, Barr::fileName);
//
//    Gnuplot plotBarrier;
//    plotBarrier.setTitle("Barrier method");
//    plotBarrier.setxLabel("x");
//    plotBarrier.setyLabel("f(x)");
//    plotBarrier.setGrid(true);
//    plotBarrier.setxRange(Barr::xBegin, -Barr::xBegin);
//    plotBarrier.setLineStyle(1, Color::GREEN, 1, 1.5);
//    plotBarrier.setLineStyle(2, Color::RED, 1, 1.5, 2, 1.0);
//    plotBarrier.setArrow(Barr::bound);
//    plotBarrier("plot x * x with lines linestyle 1, 'barrier_result.txt' with linespoints linestyle 2");
//
//    Gnuplot plotBarrierFunctions;
//    plotBarrierFunctions.setLineStyle(1, Color::GREEN, 1, 1.5);
//    plotBarrierFunctions.setLineStyle(2, Color::RED, 1, 1.5);
//    plotBarrier.setArrow(Barr::bound);

//    FILE *fp;
//    std::string str = "b";
//    std::string fname;
//    const std::vector<double> &rkVector = barrierFunctionMethod->getRkVector();
//    unsigned iNum = barrierFunctionMethod->getIterationsNumber();
//    double x, y;
//    double dx = 1e-1;
//    int xNum = (int) (Barr::xBegin - Barr::bound) / dx;
//    xNum = abs(xNum);
//    const FuncType & f = barrierFunctionMethod->getFunc();
//
//    for (unsigned i = 0; i < iNum; i++) {
//        fname = str + std::to_string(i);
//        fp = fopen(fname.c_str(), "w");
//        x = Barr::xBegin;
//        barrierFunctionMethod->setRk(rkVector[i]);
//        for (unsigned j = 0; i < xNum; i++) {
//            y = f(x);
//            fprintf(fp, "%lf %lf\n", x, y);
//            x += dx;
//        }
//
//        fclose(fp);
//
//    }

    delete(gradientMethod);
//    delete(barrierFunctionMethod);
    return 0;
}
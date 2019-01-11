#include <iostream>
#include "GradientMethod.h"
#include "Gnuplot.h"

double f(double x) {
    return x * x;
}

void printResult(const GradientMethod *gradientMethod, const std::string & funcAsString = "", bool verbosity = false) {
    std::cout << "\t\tGradient method for " << funcAsString << std::endl;
    std::cout << "xBegin = " << gradientMethod->getXBegin() << "; lambda = " << gradientMethod->getLambda() << "; eps = " << gradientMethod->getEps() << std::endl;
    if (verbosity) {
        std::cout << "i\tx" << std::endl;
        for (unsigned i = 0; i < gradientMethod->getXVector().size(); i++) {
            std::cout << i << "\t" << gradientMethod->getXVector()[i] << std::endl;
        }
    }
    std::cout << "Number of iterations = " << gradientMethod->getIterationsNumber() << std::endl;
    std::cout << "xMin = " << gradientMethod->getXMin() << std::endl;
    std::cout << "f(xMin) = " << f(gradientMethod->getXMin()) << std::endl;
}

void printResultToFile(const GradientMethod *gradientMethod, const char * fileName) {
    FILE *fp = fopen(fileName, "w");

    if (fp == nullptr) {
        std::cerr << "Can not open file " << fileName << std::endl;
        return;
    }

    const std::vector<double> & result = gradientMethod->getXVector();
    const FuncPointer & f = gradientMethod->getFunc();

    for (double i : result) {
        fprintf(fp, "%lf %lf\n", i, f(i));
    }

    fclose(fp);
}

int main() {
    double xBegin = -10.0f, lambda = 0.1, eps = 1e-3;
    auto *gradientMethod = new GradientMethod(xBegin, lambda, eps, f);
    gradientMethod->solve();
    printResult(gradientMethod, "y = x * x", false);
    const char * fileName = "../result.txt";
    printResultToFile(gradientMethod, fileName);

    Gnuplot plot;
    plot.setxLabel("x");
    plot.setyLabel("f(x)");
    plot.setGrid(true);
    plot.setxRange(xBegin, -xBegin);
    plot.setLineStyle(1, Color::GREEN, 1, 1.5);
    plot.setLineStyle(2, Color::RED, 1, 1.5, 2, 1.0);
    plot("plot x * x with lines linestyle 1, 'result.txt' with linespoints linestyle 2");

    delete(gradientMethod);
    return 0;
}
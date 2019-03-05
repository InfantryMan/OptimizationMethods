#include <iostream>
#include "GradientMethod.h"
#include "Gnuplot.h"
#include "BarrierFunctionMethod.h"
#include "Point.h"

// Функция сферы
// Min: f(0, 0) = 0
double sphereFunc(Point p) {
    return p.x * p.x + p.y * p.y;
}

// Функция Била
// Min: f(3, 0.5) = 0
double bilFunc(Point p) {
    return pow(1.5 - p.x + p.x * p.y, 2) + pow(2.25 - p.x + p.x * p.y * p.y, 2) + pow(2.625 - p.x + p.x * pow(p.y, 3), 2);
}

// Функция Розенброка
// Min: f(3, 0.5) = 0
double rozenbrokFunc(Point p) {
    return 100 * pow(p.y - p.x * p.x, 2) + pow(p.x - 1, 2);
}

// Ограничивающая функция , < 2
double boundRozenbrokFunc(Point p) {
    return p.x * p.x + p.y * p.y;
}

//double f(Point p) {
//    return 4 * pow(p.x - 5, 2) + (p.y - 6);
//}

namespace Barr {
    struct Settings {
        Point pBegin;
        double rk, C, eps;
        double bound;
        bool isLeft;
        std::string fileName;

        Settings(Point pBegin, double eps, double rk, double C, double bound, bool isLeft, std::string fileName):
            pBegin(pBegin), eps(eps), rk(rk), C(C), bound(bound), isLeft(isLeft), fileName(fileName) {}
    } rozenbrokSettings(Point(-5.0f,5.0f), 1e-2, 10.0f, 2.0f, 2.0f, true, "barrier_rozenbrok.txt");

    void rozenbrokFuncOpt(BarrierFunctionMethod &barrierFunctionMethod) {
        barrierFunctionMethod.setPBegin(rozenbrokSettings.pBegin);
        barrierFunctionMethod.setEps(rozenbrokSettings.eps);
        barrierFunctionMethod.setRk(rozenbrokSettings.rk);
        barrierFunctionMethod.setC(rozenbrokSettings.C);
        barrierFunctionMethod.setBound(rozenbrokSettings.bound);
        barrierFunctionMethod.setIsLeft(rozenbrokSettings.isLeft);

        barrierFunctionMethod.setFunc(rozenbrokFunc);
        barrierFunctionMethod.setBoundFunc(boundRozenbrokFunc);
    }
}

namespace Grad {
    struct Settings {
        Point pBegin;
        double eps;
        std::string fileName;

        Settings(Point pBegin, double eps, std::string fileName): pBegin(pBegin), eps(eps), fileName(fileName) {}
    }
    sphereSettings(Point(-81245.43f, 0.001f), 1e-3, "gradient_sphere.txt"),
    bilSettings(Point(3.5, 1.0f), 1e-3, "gradient_bil.txt"),
    rozenbrokSettings(Point(-1.5f, 1.5f), 1e-3, "gradient_rozenbrok.txt");

    void sphereFuncOpt(GradientMethod &gradientMethod) {
        gradientMethod.setEps(sphereSettings.eps);
        gradientMethod.setPBegin(sphereSettings.pBegin);
        gradientMethod.setFunc(sphereFunc);

        gradientMethod.solve();
    }

    void bilFuncOpt(GradientMethod &gradientMethod) {
        gradientMethod.setEps(bilSettings.eps);
        gradientMethod.setPBegin(bilSettings.pBegin);
        gradientMethod.setFunc(bilFunc);

        gradientMethod.solve();
    }

    void rozenbrokFuncOpt(GradientMethod &gradientMethod) {
        gradientMethod.setEps(rozenbrokSettings.eps);
        gradientMethod.setPBegin(rozenbrokSettings.pBegin);
        gradientMethod.setFunc(rozenbrokFunc);

        gradientMethod.solve();
    }

}

void printMethodResultToTerminal(const Method &method, const std::string & methodName, const std::string & funcAsString, const std::string & description = "", bool verbosity = false) {
    std::cout << "\t\t" << methodName << " method for " << funcAsString << std::endl;
    std::cout << "xBegin = " << method.getPBegin().x << " " << "yBegin = " << method.getPBegin().y << "; eps = " << method.getEps() << std::endl;
    std::cout << description << std::endl;
    if (verbosity) {
        Point p;
        std::cout << "i\tx\t\ty\t\tf" << std::endl;
        for (unsigned i = 0; i < method.getStepVec().size(); i++) {
            p = Point(method.getStepVec()[i].x, method.getStepVec()[i].y);
            std::cout << i << "\t" << std::scientific << method.getStepVec()[i].x << "\t" << method.getStepVec()[i].y << "\t" << method.getFunc()(p) << std::endl;
        }
    }
    std::cout << "Number of iterations = " << method.getIterationsNumber() << std::endl;
    std::cout << "xMin = " << method.getResult().x << " " << "yMin = " << method.getResult().y << std::endl;
    std::cout << "f(xMin, yMin) = " << method.getFunc()(method.getResult()) << std::endl;
}

void printMethodResultToFile(const Method &method, const std::string& fileName) {
    FILE *fp = fopen(fileName.c_str(), "w");

    if (fp == nullptr) {
        std::cerr << "Can not open file " << fileName << std::endl;
        return;
    }

    const std::vector<Point> & result = method.getStepVec();
    const FuncType & f = method.getFunc();

    for (Point point : result) {
        fprintf(fp, "%lf %lf %lf\n", point.x, point.y, f(point));
    }

    fclose(fp);
}

int main() {
    // Градиентный метод
    GradientMethod gradientMethod;

    // Инициализация параметров gnuplot
    Gnuplot plotGradient;
    plotGradient.setTitle("Barrier method");
    plotGradient.setxLabel("x");
    plotGradient.setyLabel("y");
    plotGradient.setGrid(true);
    plotGradient.setLineStyle(1, Color::GREEN, 1, 1.5);
    plotGradient.setLineStyle(2, Color::RED, 1, 1.5, 2, 1.0);
    plotGradient.setLineStyle(3, Color::BLUE, 1, 1.5);

    std::cout << rozenbrokFunc(Point(1.0f, 1.0f)) << std::endl;

//    // Градиентный метод для функции сферы
//    Grad::sphereFuncOpt(gradientMethod);
//    printMethodResultToTerminal(gradientMethod, "Gradient", "z = x * x + y * y", "", true);
//    printMethodResultToFile(gradientMethod, Grad::sphereSettings.fileName);
//    gradientMethod.reset();
//
//    plotGradient.setxRange(Grad::sphereSettings.pBegin.x, -Grad::sphereSettings.pBegin.x);
//    plotGradient.setyRange(Grad::sphereSettings.pBegin.y, -Grad::sphereSettings.pBegin.y);
//    plotGradient("splot x * x + y * y with lines linestyle 1, 'gradient_sphere.txt' with linespoints linestyle 2");
//
//
//    // Градиентный метод для функции Била
//    Grad::bilFuncOpt(gradientMethod);
//    printMethodResultToTerminal(gradientMethod, "Gradient", "Bill Function", "", true);
//    printMethodResultToFile(gradientMethod, Grad::bilSettings.fileName);
//
//    plotGradient.setxRange(Grad::bilSettings.pBegin.x, -Grad::bilSettings.pBegin.x);
//    plotGradient.setyRange(Grad::bilSettings.pBegin.y, -Grad::bilSettings.pBegin.y);
//    plotGradient("splot (1.5-x+x*y)**2+(2.25-x+x*y*y)**2+(2.625-x+x*y*y*y)**2 with lines linestyle 1, 'gradient_bil.txt' with linespoints linestyle 2");

    // Барьерный метод для функции Розенброка
    Grad::rozenbrokFuncOpt(gradientMethod);
    printMethodResultToTerminal(gradientMethod, "Barrier", "Rozenbrok Function", "", true);
    // printMethodResultToFile(gradientMethod, Grad::rozenbrokSettings.fileName);

    plotGradient.setxRange(Grad::rozenbrokSettings.pBegin.x, -Grad::rozenbrokSettings.pBegin.x);
    plotGradient.setyRange(Grad::rozenbrokSettings.pBegin.y, -Grad::rozenbrokSettings.pBegin.y);
    plotGradient("splot (1-x)**2+100*(y-x*x)**2 with lines linestyle 1, 'gradient_rozenbrok.txt' with linespoints linestyle 2, x*x+y*y-2 with lines linestyle 3");
    //plotGradient("splot (1-x)**2+100*(y-x*x)**2 with lines linestyle 1");


//    // Метод барьерных функций
//    BarrierFunctionMethod barrierFunctionMethod;
//    plotGradient.setTitle("BarrierFunctionMethod");
//
//    // Метод барьерных функций для функции Розенброка
//    plotGradient.setxRange(Barr::rozenbrokSettings.pBegin.x, -Barr::rozenbrokSettings.pBegin.x);
//    plotGradient.setyRange(Barr::rozenbrokSettings.pBegin.y, -Barr::rozenbrokSettings.pBegin.y);
//
//    plotGradient("splot x**2 + y**2 - 2 with lines linestyle 1");




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

//    delete(gradientMethod);
//    delete(barrierFunctionMethod);
    return 0;
}
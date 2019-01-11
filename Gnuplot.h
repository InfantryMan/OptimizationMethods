//
// Created by rustam on 11.01.19.
//

#ifndef METHODSOFOPTIMIZATION_GNUPLOT_H
#define METHODSOFOPTIMIZATION_GNUPLOT_H

#include <cstdio>
#include <iostream>
#include "Color.h"

#ifdef WIN32
    #define GNUPLOT_NAME "pgnuplot -persist"
#else
    #define GNUPLOT_NAME "gnuplot -persist"
#endif

class Gnuplot {

private:
    FILE *gnuplotPipe;
public:
    Gnuplot();
    ~Gnuplot();

    void setxLabel(const char * xLabel);
    void setyLabel(const char * yLabel);
    void setGrid(bool f);
    void setxRange(double left, double right);
    void setyRange(double left, double right);
    void setLineStyle(int number, Color color, unsigned lineType, double lineWidth, int pointType, double pointSize);
    void operator()(const std::string & command);
};

Gnuplot::Gnuplot() {
    #ifdef WIN32
        gnuplotPipe = _popen(GNUPLOT_NAME, "w");
    #else
        gnuplotPipe = popen(GNUPLOT_NAME, "w");
    #endif

    if (!gnuplotPipe) {
        std::cerr << "Gnuplot not found!" << std::endl;
    }
}

Gnuplot::~Gnuplot() {
    fprintf(gnuplotPipe, "exit");

    #ifdef WIN32
        _pclose(gnuplotPipe);
    #else
        pclose(gnuplotPipe);
    #endif
}

void Gnuplot::operator()(const std::string &command) {
    fprintf(gnuplotPipe, "%s\n", command.c_str());
    fflush(gnuplotPipe);
}

void Gnuplot::setxLabel(const char *xLabel) {
    fprintf(gnuplotPipe, "set xlabel \"%s\"\n", xLabel);
}

void Gnuplot::setyLabel(const char *yLabel) {
    fprintf(gnuplotPipe, "set ylabel \"%s\"\n", yLabel);
}

void Gnuplot::setGrid(bool f) {
    if (f) {
        fprintf(gnuplotPipe, "set grid\n");
    } else {
        fprintf(gnuplotPipe, "unset grid\n");
    }
}

void Gnuplot::setxRange(const double left, const double right) {
    fprintf(gnuplotPipe, "set xrange [%lf:%lf]\n", left, right);
}

void Gnuplot::setyRange(const double left, const double right) {
    fprintf(gnuplotPipe, "set yrange [%lf:%lf]\n", left, right);
}

void Gnuplot::setLineStyle(const int number, Color color, unsigned lineType, double lineWidth, int pointType = -1, double pointSize = -1) {
    std::string colorString;
    switch (color) {
        case Color::RED: colorString = "#dd181f";
        break;
        case Color::GREEN: colorString = "#00f0ad";
        break;
        default: colorString = "#00f0ad";
    }
    fprintf(gnuplotPipe, "set style line %d linecolor rgb \'%s\' linetype %d linewidth %lf ", number, colorString.c_str(), lineType, lineWidth);
    if (pointType != -1) {
        fprintf(gnuplotPipe, "pointtype %d ", pointType);
    }
    if (pointSize != -1) {
        fprintf(gnuplotPipe, "pointsize %lf ", pointSize);
    }
    fprintf(gnuplotPipe, "\n");
}

#endif //METHODSOFOPTIMIZATION_GNUPLOT_H

/*
 * anomaly_detection_util.cpp
 *
 * Author: 318509700 Peleg
 *         207984956 Nadav
 */
#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>

using namespace std;

//Helper method to calculate mean or expected value
float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

//method to calculate variance
float var(float *x, int size) {
    float sum = 0;
    float meanResult = avg(x, size);
    for (int i = 0; i < size; ++i) {
        sum += x[i] * x[i];
    }
    return sum / size - meanResult * meanResult;
}

//method to calculate covariance
float cov(float *x, float *y, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i] * y[i];
    }
    sum = sum / size;
    return sum - avg(x, size) * avg(y, size);
}

//method to calculate pearson
float pearson(float *x, float *y, int size) {
    float covResult = cov(x, y, size);
    float xDeviation = sqrt(var(x, size));
    float yDeviation = sqrt(var(y, size));
    return covResult / (xDeviation * yDeviation);
}

//method to calculate linear_reg
Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; ++i) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float b = avg(y, size) - a * (avg(x, size));
    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    // the Y val of point that appear in the line with the x val of the point
    float pointY = l.f(p.x);
    float yDeviation = pointY - p.y;
    return fabs(yDeviation);
}

float distancePoint (Point a, Point b){
     float dis = pow(b.x - a.x, 2) + pow(b.y - a.y, 2) * 1.0;
    return sqrt(dis);
}
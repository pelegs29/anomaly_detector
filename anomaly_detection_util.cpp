#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

#define EPSILON    (1.0E-3)
using namespace std;

// returns the variance of X and Y
//float var(float *x, int size) {
//    float sum = 0;
//    for (int i = 0; i < size; ++i) {
//        sum = sum + pow(x[i], 2);
//    }
//    float middleSum = sum / (float) size;
//    return middleSum - pow(meanCalc(x, size), 2);
//}

float var(float *x, int size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + (x[i] * x[i]);
    }
    double middleSum = sum / size;
    return middleSum - (meanCalc(x, size) * meanCalc(x, size));
}

//Helper method to calculate mean or expected value
float meanCalc(const float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + x[i];
    }
    return sum / size;
}

float cov(float *x, float *y, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + ((x[i] - meanCalc(x, size)) * (y[i] - meanCalc(y, size)));
    }
    return sum / (float) (size - 1);
}

bool isEqual(float a, float b) {
    return fabs(a - b) < EPSILON;
}

float pearson(float *x, float *y, int size) {
    float covResult = cov(x, y, size);
    float xDeviation = sqrt(var(x, size));
    float yDeviation = sqrt(var(y, size));
    return covResult / (xDeviation * yDeviation);
}

Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; ++i) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size) / var(x, size);
    float avgY = meanCalc(y, size);
    float avgX = meanCalc(x, size);
    float b = avgY - a * avgX;
    Line *line = new Line(a, b);
    return *line;
}

int main() {
    cout << "test for cov:" << endl << "Test 1:";
    float X[] = {5, 20, 40, 80, 100};
    int sizeX = sizeof(X) / sizeof(X[0]);
    float Y[] = {10, 24, 33, 54, 10};
    int sizeY = sizeof(Y) / sizeof(Y[0]);
    if (sizeX == sizeY && isEqual(cov(X, Y, sizeY), 187.75))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    cout << "Test 2:";
    float X2[] = {65.21, 64.75, 65.26, 65.76, 65.96};
    int sizeX2 = sizeof(X2) / sizeof(X2[0]);
    float Y2[] = {67.25, 66.39, 66.12, 65.70, 66.64};
    int sizeY2 = sizeof(Y2) / sizeof(Y2[0]);

    if (sizeX2 == sizeY2 && isEqual(cov(X2, Y2, sizeY2), -0.0580511))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;

    cout << "test for var:" << endl << "Test 1:";
    if (isEqual(var(X, sizeX), 1284))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    cout << "Test 2:";
    if (isEqual(var(Y, sizeY), 269.76))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    cout << "Test 3:";
    if (isEqual(var(X2, sizeX2), 0.184136))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;

    cout << "test for pearson:" << endl << "Test 1:";
    if (isEqual(pearson(X, Y, sizeY), 0.2552))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;

    //test for line

    cout << "test for Liner:" << endl << "Test 1:";

      //from wiki https://en.wikipedia.org/wiki/Simple_linear_regression
        Point* points1[15];
        points1[0] = new Point(1.47, 52.21);
        points1[1] = new Point(1.50, 53.12);
        points1[2] = new Point(1.52, 54.48);
        points1[3] = new Point(1.55, 55.84);
        points1[4] = new Point(1.57, 57.20);
        points1[5] = new Point(1.60, 58.57);
        points1[6] = new Point(1.63, 59.93);
        points1[7] = new Point(1.65, 61.29);
        points1[8] = new Point(.68, 63.11);
        points1[9] = new Point(1.70, 64.47);
        points1[10] = new Point(1.73, 66.28);
        points1[11] = new Point(1.75, 68.10);
        points1[12] = new Point(1.78, 69.92);
        points1[13] = new Point(1.80, 72.19);
        points1[14] = new Point(1.83, 74.46);

        Line lineResult1 = linear_reg(points1, 5);
        if (isEqual(lineResult1.a, -39.7468) && isEqual(lineResult1.b,61.6746))
            cout << " Passed!" << endl;
        else
            cout << " Failed!" << endl;


//from https://www.andrews.edu/~calkins/math/edrm611/edrm06.htm

    cout << " test 2:" << endl;
    Point* points2[5];
    points2[0] = new Point(1, 4);
    points2[1] = new Point(3, 2);
    points2[2] = new Point(4, 1);
    points2[3] = new Point(5, 0);
    points2[4] = new Point(8, 0);
    Line lineResult2 =   linear_reg(points2, 5);
    if (isEqual(lineResult2.a, -05746) && isEqual(lineResult2.b,3.8134))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;

    return 0;
}
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

#define EPSILON    (1.0E-3)
using namespace std;

// returns the variance of X and Y
float var(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum = sum + pow(x[i], 2);
    }
    float middleSum = sum / (float) size;
    return middleSum - pow(meanCalc(x, size), 2);
}

//Helper method to calculate mean or expected value
float meanCalc(const float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / (float) size;
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

    if (sizeX2 == sizeY2 && isEqual(cov(X2, Y2, sizeY2),-0.0580511))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;

    cout << "test for var:" << endl << "Test 1:";
    if (isEqual(var(X, sizeX),1284))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    cout << "Test 2:";
    if (isEqual(var(Y, sizeY),269.76))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    cout << "Test 3:";
    if (isEqual(var(X2, sizeX2),0.184136))
        cout << " Passed!" << endl;
    else
        cout << " Failed!" << endl;
    return 0;
}
#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;

//Helper method to calculate mean or expected value
float meanCalc(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return (1 / size) * sum;
}

float cov(float *x, float *y, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += ((x[i] - meanCalc(x, size)) * (y[i] - meanCalc(y, size)));
    }
    return (1 / (size - 1)) * sum;
}

int main() {
    float X[] = {65.21, 64.75, 65.26, 65.76, 65.96};
    int sizeX = sizeof(X) / sizeof(X[0]);
    float Y[] = {67.25, 66.39, 66.12, 65.70, 66.64};
    int sizeY = sizeof(Y) / sizeof(Y[0]);

    if (sizeX == sizeY){
        cout << cov(X, Y, sizeY);
    }
    return 0;
}
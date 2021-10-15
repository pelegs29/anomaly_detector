#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;

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

int main() {
    float X[] ={5, 20, 40, 80, 100};
    int sizeX = sizeof(X) / sizeof(X[0]);
    float Y[] = {10, 24, 33, 54, 10};
    int sizeY = sizeof(Y) / sizeof(Y[0]);

    if (sizeX == sizeY) {
        cout << cov(X, Y, sizeY);
    }
    return 0;
}
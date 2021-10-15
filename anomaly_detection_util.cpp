#include "anomaly_detection_util.h"

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
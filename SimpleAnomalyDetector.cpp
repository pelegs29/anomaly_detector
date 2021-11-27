
//* Author: 318509700 Peleg
//*         207984956 Nadav
#include <memory>
#include "SimpleAnomalyDetector.h"

#define CORR_THRESHOLD 0.9
using namespace std;

/**
 * default constructor for correlatedFeatures struct
 * @param feature1 string of the first feature of the correlated couple
 * @param feature2 string of the first feature of the correlated couple
 * @param corrlation the calculated correlation between them
 * @param linReg Line of the linear regression
 * @param threshold float representing the maximum value that isn't anomaly
 */
correlatedFeatures::correlatedFeatures(string feature1, string feature2, float corrlation,
                                       const Line &linReg, float threshold) :
        feature1(move(feature1)), feature2(move(feature2)),
        corrlation(corrlation), lin_reg(linReg),
        threshold(threshold) {}

//constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    vector<correlatedFeatures> correlatedFeatures;
    this->cf = correlatedFeatures;
}

//destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {}

/**
 * method to calculated the max deviation between array of points and regression line
 * @param reg given regression Line
 * @param points_arr given array of Points
 * @param size given size of points_arr
 * @return float representation of the max deviation found
 */
float maxDeviation(Line reg, Point **points_arr, int size) {
    float maxDev = 0;
    for (int i = 0; i < size; ++i) {
        float currentDev = abs(points_arr[i]->y - reg.f(points_arr[i]->x));
        //float currentDev = dev(*(points_arr[i]), reg);
        if (currentDev > maxDev)
            maxDev = currentDev;
    }
    return maxDev;
}

/**
 * method to create a pointer to an array of Point pointers from two arrays,
 * one representing the x values and the other the y values accordingly.
 * @param x given array of float x values
 * @param y given array of float y values
 * @param size given size of x or y array
 * @return a pointer to an array of Point pointers
 */
Point **createPointsArr(float *x, float *y, int size) {
    Point **points_arr = new Point *[size];
    for (int i = 0; i < size; ++i) {
        points_arr[i] = new Point(x[i], y[i]);
    }
    return points_arr;
}

/**
 * simple method that free the allocated points array.
 * @param arr given pointer to the Points array to be freed
 * @param size given arr size
 */
void freePointsArr(Point **arr, int size) {
    for (int i = 0; i < size; ++i) {
        delete arr[i];
    }
    delete[] arr;
}

/**
 * method to create vector of correlatedFeatures in the TimeSeries given
 * @param ts given TimeSeries data to be learned from.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    vector<correlatedFeatures> correlatedFound;
    vector<pair<string, vector<float>>> data = ts.getData();
    // flag -> if no correlativeDuo found
    for (int i = 0; i < data.size() - 1; ++i) {
        int correlativeDuo = -1;
        float currentMax = CORR_THRESHOLD;
        //pResult will hold the current correlation between feature i and j
        float pResult = 0;
        float *featureIArray = &data[i].second[0];
        int featureSize = (int) data[i].second.size();
        for (int j = i + 1; j < data.size(); ++j) {
            float *featureJArray = &data[j].second[0];
            pResult = fabs(pearson(featureIArray, featureJArray, featureSize));
            //if a better correlation found save the index and update the currentMax
            if (currentMax < pResult) {
                currentMax = pResult;
                correlativeDuo = j;
            }
        }
        //if a correlation has been found, create a correlatedFeature and add it the SimpleAnomalyDetector vector
        if (correlativeDuo != -1) {
            Point **points_arr = createPointsArr(&data[i].second[0],
                                                 &data[correlativeDuo].second[0], featureSize);
            Line linearReg = linear_reg(points_arr, featureSize);
            float regThreshold = maxDeviation(linearReg, points_arr, featureSize) * 1.1;
            correlatedFeatures duoFound = correlatedFeatures(data[i].first,
                                                             data[correlativeDuo].first,
                                                             currentMax, linearReg, regThreshold);
            this->cf.push_back(duoFound);
            freePointsArr(points_arr, featureSize);
        }
    }
}

/**
 * the function detect variant
 * @param ts a data contain new information that need to detect variant
 * @return vector of anomalyReport contain the time and the 2 features involve in the variant
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    //the number of row data in ts
    int rowSize = ts.getData()[0].second.size(); // just get the number of row of the first float vector in ts
    vector<AnomalyReport> vectorReport;
    vector<correlatedFeatures> correlVector = this->getNormalModel();
    for (auto & correlatedDuo : correlVector) {
        //get the correlatedFeatures that we check now (the J item in the vector)
        string features1 = correlatedDuo.feature1;
        string features2 = correlatedDuo.feature2;
        for (int row = 0; row < rowSize; row++) {
            if (row == 98){
                int u= 5;
            }
            //get the data of the features in the time that we check from the data ts
            float features1Data = ts.getInfoByRow(row, features1);
            float features2Data = ts.getInfoByRow(row, features2);
            Point featuresPoint = Point(features1Data, features2Data);
            //float devCheck = dev(featuresPoint, correlatedDuo.lin_reg);
            float devCheck =abs(featuresPoint.y - correlatedDuo.lin_reg.f(featuresPoint.x));
            if (devCheck > correlatedDuo.threshold) {
                //there is a variant that we found
                //creat new report and add it to the reportvector;
                AnomalyReport anomalyReport = AnomalyReport(features1 + "-" + features2, row + 1);
                vectorReport.push_back(anomalyReport);
            }
        }
    }
    return vectorReport;
}


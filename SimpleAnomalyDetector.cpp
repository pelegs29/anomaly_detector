#include <memory>
#include "SimpleAnomalyDetector.h"

#define CORR_THRESHOLD 0.7
using namespace std;

correlatedFeatures::correlatedFeatures(string feature1, string feature2, float corrlation,
                                       const Line &linReg, float threshold) :
        feature1(move(feature1)), feature2(move(feature2)),
        corrlation(corrlation), lin_reg(linReg),
        threshold(threshold) {}

//constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub
}

//destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

float maxDeviation(Line reg, Point **points_arr, int size) {
    float maxDev = 0;
    for (int i = 0; i < size; ++i) {
        float currentDev = dev(*(points_arr[i]), reg);
        if (currentDev > maxDev)
            maxDev = currentDev;
    }
    return maxDev;
}

Point **createPointsArr(float *x, float *y, int size) {
    auto **points_arr = new Point *[size];
    for (int i = 0; i < size; ++i) {
        points_arr[i] = new Point(x[i], y[i]);
    }
    return points_arr;
}

void freePointsArr(Point **arr, int size) {
    for (int i = 0; i < size; ++i) {
        delete arr[i];
    }
    delete arr;
}

//method to create vector of correlatedFeatures in the TimeSeries given
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
            float regThreshold = maxDeviation(linearReg, points_arr, featureSize) * 1.1f;
            correlatedFeatures duoFound = correlatedFeatures(data[i].first,
                                                             data[correlativeDuo].first,
                                                             currentMax, linearReg, regThreshold);
            this->cf.push_back(duoFound);
            freePointsArr(points_arr, featureSize);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> vectorReport;
    vector<correlatedFeatures> correlVector = this->getNormalModel();
    //vector of the time of the data that we need to check
    vector<float> timeVector = ts.getData()[0].second;
    //move row by row and check the data
    for (int row = 0; row < ts.getData()[0].second.size(); ++row) {
        for (const auto &correlatedFeature: correlVector) {
            //get the correlatedFeatures that we check now (the J item in the vector)
            string features1 = correlatedFeature.feature1;
            string features2 = correlatedFeature.feature2;
            //get the data of the features in the time that we check from the data ts
            float features1Data = ts.getInfo(timeVector[row], features1);
            float features2Data = ts.getInfo(timeVector[row], features2);
            //creat a point contain the data from fracture 1 and 2, and check if it is bigger form the threshold
            Point featuresPoint = Point(features1Data, features2Data);
            float devCheck = dev(featuresPoint, correlatedFeature.lin_reg);
            if (devCheck > correlatedFeature.threshold) {
                //there is a variant that we found
                //creat new report and add it to the reportvector;
                AnomalyReport anomalyReport = AnomalyReport(features1 + "-" + features2, row + 1);
                vectorReport.push_back(anomalyReport);
            }
        }
    }
    return vectorReport;
}


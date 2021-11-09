#include <memory>
#include "SimpleAnomalyDetector.h"

#define THRESHOLD 0.7
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
    int correlativeDuo = -1;
    for (int i = 0; i < data.size(); ++i) {
        float currentMax = THRESHOLD;
        //pResult will hold the current correlation between feature i and j
        float pResult;
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
            correlatedFeatures duoFound = correlatedFeatures(data[i].first,
                                                             data[correlativeDuo].first,
                                                             currentMax, linearReg, THRESHOLD);
            this->cf.push_back(duoFound);
            freePointsArr(points_arr, featureSize);
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}



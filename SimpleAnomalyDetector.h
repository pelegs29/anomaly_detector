

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

#define CORR_THRESHOLD 0.9


struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    float xCenter;
    float yCenter;

    correlatedFeatures(string feature1, string feature2, float corrlation, const Line &linReg,
                       float threshold, float x, float y);
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {

public:
    vector<correlatedFeatures> cf;
    float threshold;

    SimpleAnomalyDetector();

    // method
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual void learnNormal(const TimeSeries &ts, float thresholdDetectorNew);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    Point **createPointsArr(float *x, float *y, int size);

    void freePointsArr(Point **arr, int size);

    virtual bool isThereAnomaly(Point featuresPoint, correlatedFeatures correlatedDuo);

    virtual void setThreshold(float input);

};


#endif /* SIMPLEANOMALYDETECTOR_H_ */

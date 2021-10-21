
#include "SimpleAnomalyDetector.h"

#define THRESHOLD 0.7;

correlatedFeatures::correlatedFeatures(string feature1, string feature2, float corrlation,
                                       const Line &linReg, float threshold) :
        feature1(std::move(feature1)), feature2(std::move(feature2)),
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

//method to create vector of correlatedFeatures in the TimeSeries given
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    vector<correlatedFeatures> correlatedFound;

    auto outerIt = ts.data.begin();
    auto innerIt = outerIt++;
    while (outerIt != ts.data.end()) {
        string correlativeDuo;
        float currentMax = THRESHOLD;
        float pResult;
        while (innerIt != ts.data.end()) {
            //TODO check if all the tables size are equal !
            std::vector<float> vector1 = outerIt->second;
            std::vector<float> vector2 = innerIt->second;
            float *featureI = &vector1[0];
            float *featureJ = &vector2[0];
            int size = (int) outerIt->second.size();
            pResult = fabs(pearson(featureI, featureJ, size));
            if (currentMax < pResult) {
                currentMax = pResult;
                correlativeDuo = innerIt->first;
            }
        }
        if (!correlativeDuo.empty())
            //TODO write some signatures in header file for TimeSeries for use in linear_reg function
            struct correlatedFeatures duoFound = correlatedFeatures(outerIt->first, innerIt->first, pResult,);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}




#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<correlatedFeatures> correlVector = this->getNormalModel();
    //move row by row and check the data
    for (int i = 0; i <  ts.data[0].second.size(); ++i) {
        for (int j = 0; j < correlVector.size(); ++j) {
            const string features1 = correlVector[i].feature1;
            const string features2 = correlVector[i].feature2;
            float features1Data = ts.getData(ts.data[0].second[i],features1);
        }
    }
}


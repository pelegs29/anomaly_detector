
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
    vector<AnomalyReport> vectorReport;
    vector<correlatedFeatures> correlVector = this->getNormalModel();
    //vector of the time of the data that we need to check
    vector<float> timeVector = ts.data[0].second;
    //move row by row and check the data
    for (int row = 0; row <  ts.data[0].second.size(); ++row) {
        for (auto correlatedFeature : correlVector) {
            //get the correlatedFeatures that we check now (the J item in the vector)
            string features1 = correlatedFeature.feature1;
            string features2 = correlatedFeature.feature2;
            //get the data of the features in the time that we check from the data ts
            float features1Data = ts.getInfo(timeVector[row],features1);
            float features2Data = ts.getInfo(timeVector[row],features2);
            //creat a point contain the data from fracture 1 and 2, and check if it is bigger form the threshold
            Point featuresPoint = Point(features1Data,features2Data);
            float devCheck = dev(featuresPoint,correlatedFeature.lin_reg);
            if(devCheck > correlatedFeature.threshold){
                //there is a variant that we found
                //creat new report and add it to the reportvector;
                AnomalyReport anomalyReport = AnomalyReport(features1+"-"+features2,row+1);
                vectorReport.push_back(anomalyReport);
            }
        }
    }
    return vectorReport;
}


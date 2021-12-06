//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "HybridAnomalyDetector.h"
#include "vector"

HybridAnomalyDetector::HybridAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
	// TODO Auto-generated destructor stub
}
/**
 * the function add  information the correlation vector
 * if 2 features have correlation between 0.5 -0.9 update there thershold by the radius of a circle contain all
 * the point of the features
 * @param ts
 */
void  HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //update the correlation vector by the Definitions of the simple detector
    SimpleAnomalyDetector::learnNormal(ts, 0.5);
    for (auto &features: this->cf) {
        // the threshold of the features is between 0.5 - 0.9 -> so we change his threshold to radius
        if (features.corrlation > this->thresholdDetector && features.corrlation < CORR_THRESHOLD) {
            int size = ts.getData()[0].second.size();
            int index1 = ts.getCategoryIndexRow(features.feature1);
            int index2 = ts.getCategoryIndexRow(features.feature2);
            Point **points_arr = SimpleAnomalyDetector::createPointsArr(&ts.getData()[index1].second[0], &ts.getData()[index2].second[0], size);
            Circle circle = findMinCircle(points_arr,size);
            features.threshold = circle.radius * 1.1;
            features.xCenter = circle.center.x;
            features.yCenter = circle.center.y;
            SimpleAnomalyDetector::freePointsArr(points_arr,size);
        }

    }
}

/**
 * the function check if a given point of correlation is anomaly or not
 * @param featuresPoint the point that need to check
 * @param correlated the correlation the the point represent
 * @return true of false if there is anomaly
 */
 bool HybridAnomalyDetector::isThereAnomaly(Point featuresPoint,correlatedFeatures correlated){
     //case 1
     bool  simple = false;
     if (correlated.corrlation >= CORR_THRESHOLD ){
         simple = SimpleAnomalyDetector::isThereAnomaly(featuresPoint,correlated);
     }

     // case 2 - check is the correlation between 0.5 -0.9
     bool hybrid = false;
     if (correlated.corrlation< CORR_THRESHOLD && correlated.corrlation>thresholdDetector) {
         Point *center = new Point(correlated.xCenter, correlated.yCenter);
         if (distancePoint(featuresPoint, *(center)) > correlated.threshold) {
             hybrid = true;
         }
     }
     if (hybrid || simple){
         return true;
     }
     return false;
}




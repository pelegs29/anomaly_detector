//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "HybridAnomalyDetector.h"
#include "vector"

HybridAnomalyDetector::HybridAnomalyDetector() {}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

/**
 * the function add  information the correlation vector
 * if 2 features have correlation between 0.5 -0.9 update there thershold by the radius of a circle contain all
 * the point of the features
 * @param ts
 */
void HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    float tempThreshold = this->thresholdDetector;
    //update the correlation vector by the Definitions of the simple detector
    SimpleAnomalyDetector::learnNormal(ts, 0.5);
    this->changeThreshold(tempThreshold);
    for (auto &features: this->cf) {
        // the threshold of the features is between 0.5 - 0.9 -> so we change his threshold to radius
        if (features.corrlation > 0.5 && features.corrlation < this->thresholdDetector) {
            int size = ts.getData()[0].second.size();
            int index1 = ts.getCategoryIndexRow(features.feature1);
            int index2 = ts.getCategoryIndexRow(features.feature2);
            Point **points_arr = SimpleAnomalyDetector::createPointsArr(&ts.getData()[index1].second[0],
                                                                        &ts.getData()[index2].second[0], size);
            Circle circle = findMinCircle(points_arr, size);
            features.threshold = circle.radius * 1.1;
            features.xCenter = circle.center.x;
            features.yCenter = circle.center.y;
            SimpleAnomalyDetector::freePointsArr(points_arr, size);
        }

    }
}

/**
 * the function check if a given point of correlation is anomaly or not
 * @param featuresPoint the point that need to check
 * @param correlated the correlation the the point represent
 * @return true of false if there is anomaly
 */
bool HybridAnomalyDetector::isThereAnomaly(Point featuresPoint, correlatedFeatures correlated) {
    //case 1
    bool simple = false;
    if (correlated.corrlation >= this->thresholdDetector) {
        simple = SimpleAnomalyDetector::isThereAnomaly(featuresPoint, correlated);
    }

    // case 2 - check is the correlation between 0.5 -0.9 (the threshold of the detector)
    bool hybrid = false;
    if (correlated.corrlation < this->thresholdDetector && correlated.corrlation > 0.5) {
        auto *center = new Point(correlated.xCenter, correlated.yCenter);
        if (distancePoint(featuresPoint, *(center)) > correlated.threshold) {
            hybrid = true;
        }
        delete center;
    }
    if (hybrid || simple) {
        return true;
    }
    return false;
}






#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"


class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    void  virtual  learnNormal(const TimeSeries &ts) ;
    virtual bool isThereAnomaly(Point featuresPoint,correlatedFeatures correlatedDuo);


};

#endif /* HYBRIDANOMALYDETECTOR_H_ */

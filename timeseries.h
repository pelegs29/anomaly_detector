

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>

using namespace std;

class TimeSeries{

public:
    map<string, vector<float>> data;
	TimeSeries(const char* CSVfileName){
	}
    map<string, vector<float>> getMap(){
        return this->data;
    }

};



#endif /* TIMESERIES_H_ */

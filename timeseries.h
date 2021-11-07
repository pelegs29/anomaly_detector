

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

using namespace std;

class TimeSeries{


private:
    //TODO: maybe delete category names
    vector<string>* categoryNames;
    vector<pair<string,vector<float>>> data;
public:
    //function
    vector<pair<string,vector<float>>> read_csv(const string& filename) const;
    //constructor
    explicit TimeSeries(const char* CSVfileName){
        this->categoryNames = new vector<string>;
        this->data =  read_csv(CSVfileName);

    }

    vector<pair<string,vector<float>>> getData() const{
        return this->data;
    }
    void buildData(const char* CSVfileName){
        this->data = read_csv(CSVfileName);
    }

    //return the number of item in the Feature column
    int getFeatureSizeColum(){
        vector<float> vector = this->data.begin()->second;
        return vector.size();

    }
    float getinfo(float time, const string& category);

    //Destructors
    ~TimeSeries(){
        free(&this->data);
        free(&this->categoryNames);
    }
};


#endif /* TIMESERIES_H_ */

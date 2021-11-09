#include <string>
#include <vector>
#include <stdexcept> // runtime_error
#include <iostream>
#include "timeseries.h"

using namespace std;
/**
 * get a string line form the data and return a vector contain the data of the line in float
 * @param line
 * @return vector coantin the data from the line in the data
 */
vector<float> fromLineToVector(const string& line){
    vector<float> vect;
    // make the string as a stream
    stringstream ss1(line);
    //read from the line number by number , between them there is a comma
    for (float i; ss1 >> i;) {
        vect.push_back(i);
        if (ss1.peek() == ',')
            ss1.ignore();
    }
    return vect;
}
/**
 *
 * @param vector contain value
 * @param time the index of the time value in the vector
 * @return the index of the value of the vector
 */
int findIndexVector(vector<float> vector, float time){
    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i] == time)
            return i;
    }
    //there is no time data in the vector
    return -1;
}
/**
 *
 * @param filename contain the name of the csv file
 * @return vector contain of pair represents the category and its value
 */
vector<pair<string,vector<float>>> TimeSeries::read_csv(const string& filename) const{
    // Reads a CSV file into a vector of <string, vector<float>> pairs where
    // each pair represents <column name, column values>
    vector<pair<string,vector<float>>> dataBuild;

    //vector contain the column names
    vector<string>& idName = *this->categoryNames;

    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    int val;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);

        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while(getline(ss, colname, ',')){

            // Initialize and add <colname, int vector> pairs to result
            vector<float> vectorptr; // the vector that contain the information of the colname
            dataBuild.emplace_back(colname,vectorptr);
            idName.push_back(colname);
        }
    }
    // Read data, line by line
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        //contain the data in the row (the float number)
        vector<float> vect = fromLineToVector(line);

        // Declaring iterator to a vector
        vector<float>::iterator ptr;

        // Displaying vector elements using begin() and end()
        for (ptr = vect.begin(); ptr < vect.end(); ptr++){
            dataBuild[colIdx].second.push_back(*ptr);
            colIdx++;
        }
    }

    // Close file
    myFile.close();
    return dataBuild;
}

float TimeSeries::getInfo(float time, string category) const {
    //get the index of the time that we need in the vector
    int indexData = findIndexVector(this->data[0].second,time);
    if (indexData == -1){
        cout<< "Error , no cant find the index please check input to Getinfo function" << endl;
        return -1;
    }
    for (int i = 0; i < data.size(); ++i) {
        string categoryName = this->data[i].first;
        if (categoryName == category){
            return this->data[i].second[indexData];
        }
    }
    //not found any mach!
    return -1;

}
//
//int main() {
//    cout << "Hello World!";
//    TimeSeries& timeSeries = *new TimeSeries("test1.csv");
//    cout << timeSeries.getFeatureSizeColum() <<endl;
//    float check =timeSeries.getinfo(0.2,"Altitude (feet)");
//    cout<< check << endl;
//
//
//
//    return 0;
//}
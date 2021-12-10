cmake_minimum_required(VERSION 3.20)  # CMake version check
project(simple_example)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(anomaly_detector
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        AnomalyDetector.h
        MainTrain.cpp
        SimpleAnomalyDetector.h
        SimpleAnomalyDetector.cpp
        timeseries.cpp
        timeseries.h minCircle.cpp minCircle.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        CLI.h
        CLI.cpp
        commands.h
        StandardIO.h StandardIO.cpp)
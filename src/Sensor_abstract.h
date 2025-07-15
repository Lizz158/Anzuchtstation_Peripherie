#pragma once
#include <map>
#include <string>
#include "Metric_Type.h"

class Sensor_abstract {
    
    protected:
        std::map<Metric_Type, std::string> metricValues;

        virtual void initialize() = 0;
        virtual std::map<Metric_Type, std::string> readValue() = 0;

        virtual ~Sensor_abstract(){};
};
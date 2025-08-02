#pragma once
#include <map>
#include <string>
#include "Metric_Type.h"

class Sensor_abstract
{

protected:
    std::map<Metric_Type, std::string> metricValues;

    virtual bool initialize() = 0;

    virtual void readValue() = 0;

    virtual void sendMqttMessage() = 0;

    virtual ~Sensor_abstract() {};
};
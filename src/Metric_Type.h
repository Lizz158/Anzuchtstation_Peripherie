#pragma once
#include <map>
#include <string>

enum class Metric_Type {
    SOIL_HUMIDITY, 
    SOIL_TEMPERATURE, 
    ROOM_HUMIDITY, 
    ROOM_TEMPERATURE, 
    LUMINOSITY
};

std::string metricTypeToString(Metric_Type type);
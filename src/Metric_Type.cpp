#include <Metric_Type.h>

std::map<Metric_Type, std::string> metricTypeMap = {
    {Metric_Type::SOIL_HUMIDITY, "bodenfeuchte"},
    {Metric_Type::SOIL_TEMPERATURE, "bodentemperatur"},
    {Metric_Type::ROOM_HUMIDITY, "raumfeuchte"},
    {Metric_Type::ROOM_TEMPERATURE, "raumtemperatur"},
    {Metric_Type::LUMINOSITY, "lichtstaerke"}
};

std::string metricTypeToString(Metric_Type type) {
    return metricTypeMap.at(type);
}
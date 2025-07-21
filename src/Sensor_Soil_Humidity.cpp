#include "Sensor_Soil_Humidity.h"

Sensor_Soil_Humidity::Sensor_Soil_Humidity() {};

void Sensor_Soil_Humidity::initialize() {};

std::map<Metric_Type, std::string> Sensor_Soil_Humidity::readValue()
{
    int sensor_Val = analogRead(A0);

    // Convert dry and wet values to a scale from 0 to 100 to get percentage value
    long humidity = map(sensor_Val, wetVal, dryVal, 100, 0);

    Serial.print("Started reading values for soil humidity: ");
    Serial.println(humidity);

    metricValues[Metric_Type::SOIL_HUMIDITY] = std::to_string(humidity);

    std::string myValue = metricValues.at(Metric_Type::SOIL_HUMIDITY);

    Serial.println("Value in map for soil moisture: ");
    Serial.println(myValue.c_str());

    delay(2000);

    return metricValues;
}

void Sensor_Soil_Humidity::sendMqttMessage()
{
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_HUMIDITY), metricTypeToString(Metric_Type::SOIL_HUMIDITY));
}

Sensor_Soil_Humidity::~Sensor_Soil_Humidity() {}
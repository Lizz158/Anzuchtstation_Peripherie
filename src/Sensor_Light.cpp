#include "Sensor_Light.h"

Sensor_Light::Sensor_Light() : isconnected(false)
{
    metricValues[Metric_Type::LUMINOSITY] = "0";
};

bool Sensor_Light::initialize()
{
    if (!isconnected)
    {
        isconnected = BH1750.begin(BH1750_TO_GROUND);
    }
    return isconnected;
}

void Sensor_Light::readValue()
{
    // isconnected = BH1750.begin(BH1750_TO_GROUND);
    if (isconnected)
    {
        isconnected = BH1750.start();
        light = BH1750.getLux(); //  waits until a conversion finished
        metricValues[Metric_Type::LUMINOSITY] = std::to_string(light);
    }
    if (!isconnected)
    {
        mqttdebug("No BH1750 sensor found!");
    }
}

void Sensor_Light::sendMqttMessage()
{
    // if(abs(oldval-newval)>cov){
    sendmqttmessage(metricValues.at(Metric_Type::LUMINOSITY), metricTypeToString(Metric_Type::LUMINOSITY));
}

Sensor_Light::~Sensor_Light() {}
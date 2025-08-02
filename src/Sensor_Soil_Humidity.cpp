#include "Sensor_Soil_Humidity.h"

Adafruit_ADS1015 Sensor_Soil_Humidity::ads;
bool Sensor_Soil_Humidity::isadsinitialized = false; // Initialize to false

Sensor_Soil_Humidity::Sensor_Soil_Humidity(double dryVal, double wetVal, uint8_t channel) : dryVal(dryVal), wetVal(wetVal), channel(channel)
{
    if(!isadsinitialized){
        ads.begin();
        isadsinitialized = true;
    }
}

void Sensor_Soil_Humidity::initialize() {}

std::map<Metric_Type, std::string> Sensor_Soil_Humidity::readValue()
{
    int adc0 = ads.readADC_SingleEnded(channel);

    double sensor_Val = double(ads.computeVolts(adc0));
    Serial.println(sensor_Val);

    // Convert dry and wet values to a scale from 0 to 100 to get percentage value
    sensor_Val = double(map(sensor_Val*100, (wetVal*100), (dryVal*100), 10000, 0)) / 100;
    Serial.println(sensor_Val);

    metricValues[Metric_Type::SOIL_HUMIDITY] = std::to_string(sensor_Val);

    std::string myValue = metricValues.at(Metric_Type::SOIL_HUMIDITY);

    return metricValues;
}

void Sensor_Soil_Humidity::sendMqttMessage()
{
    std::string topic = "feuchtigkeit";
    topic.append(std::to_string(channel+1));
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_HUMIDITY), topic);
}

Sensor_Soil_Humidity::~Sensor_Soil_Humidity() {}
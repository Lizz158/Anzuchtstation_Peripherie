#include "Sensor_Soil_Humidity.h"

Adafruit_ADS1015 Sensor_Soil_Humidity::ads;
bool Sensor_Soil_Humidity::isadsinitialized = false; // Initialize to false

Sensor_Soil_Humidity::Sensor_Soil_Humidity(double dryVal, double wetVal, uint8_t channel, std::string topic) : dryVal(dryVal), wetVal(wetVal), channel(channel), topic(topic)
{
    metricValues[Metric_Type::SOIL_HUMIDITY] = "0";
}

bool Sensor_Soil_Humidity::initialize()
{
    if(!isadsinitialized){
        isadsinitialized = ads.begin();
    }
    return isadsinitialized;
}

void Sensor_Soil_Humidity::readValue()
{
    if (isadsinitialized){
        int adc0 = ads.readADC_SingleEnded(channel);

        double sensor_Val = double(ads.computeVolts(adc0));

        // Convert dry and wet values to a scale from 0 to 100 to get percentage value
        sensor_Val = double(map(sensor_Val*100, (wetVal*100), (dryVal*100), 10000, 0)) / 100;

        metricValues[Metric_Type::SOIL_HUMIDITY] = std::to_string(sensor_Val);

        std::string myValue = metricValues.at(Metric_Type::SOIL_HUMIDITY);
    }else{
        mqttdebug("ADS1015 nicht verbunden");
    }

}

void Sensor_Soil_Humidity::sendMqttMessage()
{
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_HUMIDITY), topic);
}

Sensor_Soil_Humidity::~Sensor_Soil_Humidity() {}
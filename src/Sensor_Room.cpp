#include "Sensor_Room.h"
#include <Arduino.h>

Sensor_Room::Sensor_Room() : bme(&Wire), bme_connected(false)
{
    metricValues[Metric_Type::ROOM_TEMPERATURE] = "0";
    metricValues[Metric_Type::ROOM_HUMIDITY] = "0";
};

bool Sensor_Room::initialize()
{
    if (!bme_connected)
    {
        if (!bme.begin())
        {   
            mqttdebug("Could not find a valid BME680 sensor.");
            bme_connected = false;
        }
        else
        {
            bme_connected = true;
            mqttdebug("BME680 connected");
            // Set up oversampling and filter initialization
            bme.setTemperatureOversampling(BME680_OS_8X);
            bme.setHumidityOversampling(BME680_OS_2X);
            bme.setPressureOversampling(BME680_OS_4X);
            bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
            bme.setGasHeater(320, 150); // 320*C for 150 ms
        }
    }
    return bme_connected;
}

void Sensor_Room::readValue()
{
    if (!bme_connected)
    {
        mqttdebug("BME680 not connected");
    }

    if (bme_connected)
    {
        if (!bme.performReading())
        {
            mqttdebug("BME680 Failed to perform reading :(");
            bme_connected = false;
        }

        metricValues[Metric_Type::ROOM_TEMPERATURE] = std::to_string(bme.temperature);
        metricValues[Metric_Type::ROOM_HUMIDITY] = std::to_string(bme.humidity);
    }
}

void Sensor_Room::sendMqttMessage()
{
    sendmqttmessage(metricValues.at(Metric_Type::ROOM_TEMPERATURE), metricTypeToString(Metric_Type::ROOM_TEMPERATURE));
    sendmqttmessage(metricValues.at(Metric_Type::ROOM_HUMIDITY), metricTypeToString(Metric_Type::ROOM_HUMIDITY));
}

Sensor_Room::~Sensor_Room() {}
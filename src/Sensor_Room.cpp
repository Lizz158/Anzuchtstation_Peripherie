#include "Sensor_Room.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

bool bme_connected = false;

Sensor_Room::Sensor_Room() : bme(&Wire), bme_connected(false) {};

void Sensor_Room::initialize()
{

    Serial.println(F("BME680 test"));

    if (!bme.begin())
    {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        bme_connected = false;
    }
    else
    {
        bme_connected = true;
        Serial.println("BME680 connected");
    }

    if (bme_connected)
    {
        // Set up oversampling and filter initialization
        bme.setTemperatureOversampling(BME680_OS_8X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_4X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme.setGasHeater(320, 150); // 320*C for 150 ms
    }
}

std::map<Metric_Type, std::string> Sensor_Room::readValue()
{

    Serial.println("Started reading values");

    if (bme_connected)
    {
        if (!bme.performReading())
        {
            Serial.println("Failed to perform reading :(");
        }

        std::string room_temperature = std::to_string(bme.temperature);
        std::string room_humidity = std::to_string(bme.humidity);

        Serial.println();

        sendmqttmessage(room_temperature, "raumtemperatur");

        metricValues[Metric_Type::ROOM_TEMPERATURE] = room_temperature;
        metricValues[Metric_Type::ROOM_HUMIDITY] = room_humidity;

        for (const auto &pair : metricValues)
        {
            Serial.print(static_cast<int>(pair.first));
            Serial.print(": ");
            Serial.println(pair.second.c_str());
        }

        delay(2000);
    }

    return metricValues;
}

void Sensor_Room::sendMqttMessage(){
    std::string myString = metricValues.at(Metric_Type::ROOM_TEMPERATURE);
    Serial.println(myString.c_str());

    sendmqttmessage(metricValues.at(Metric_Type::ROOM_TEMPERATURE), metricTypeToString(Metric_Type::ROOM_TEMPERATURE));
    sendmqttmessage(metricValues.at(Metric_Type::ROOM_HUMIDITY), metricTypeToString(Metric_Type::ROOM_HUMIDITY));
}

Sensor_Room::~Sensor_Room() {}
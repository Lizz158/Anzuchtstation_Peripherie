#include <Sensor_Soil_Temperature.h>

Sensor_Soil_Temperature::Sensor_Soil_Temperature(uint8_t pin) : oneWire(pin),
                                                          sensors(&oneWire),
                                                          temperature(404) {};

void Sensor_Soil_Temperature::initialize()
{
    sensors.begin();
}

std::map<Metric_Type, std::string> Sensor_Soil_Temperature::readValue()
{
    Serial.println("Started reading values for soil temperature");

    sensors.requestTemperatures();

    temperature = sensors.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C)
    {
        Serial.println("404");
    }

// std::string bodentemperature1 = std::to_string(temperature.getreading());
  // sendmqttmessage(bodentemperature1, "bodentemperatur1");
  // delay(2000);


    metricValues[Metric_Type::SOIL_TEMPERATURE] = temperature;

    for (const auto &pair : metricValues)
    {
        Serial.print(static_cast<int>(pair.first));
        Serial.print(": ");
        Serial.println(pair.second.c_str());
    }

    return metricValues;
}

void Sensor_Soil_Temperature::sendMqttMessage() {
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_TEMPERATURE), metricTypeToString(Metric_Type::SOIL_TEMPERATURE));
}

Sensor_Soil_Temperature::~Sensor_Soil_Temperature() {}
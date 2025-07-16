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
    sensors.requestTemperatures();

    temperature = sensors.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C)
    {
        Serial.println("404");
        return metricValues;
    }

    Serial.println('Started reading values for soil temperature: ' + temperature);

    metricValues[Metric_Type::SOIL_TEMPERATURE] = temperature;

    Serial.println('Value in map for soil temperature: ');

    for (const auto &pair : metricValues)
    {
        Serial.print(static_cast<int>(pair.first));
        Serial.print(": ");
        Serial.println(pair.second.c_str());
    }

    delay(2000);

    return metricValues;
}

void Sensor_Soil_Temperature::sendMqttMessage() {
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_TEMPERATURE), metricTypeToString(Metric_Type::SOIL_TEMPERATURE));
}

Sensor_Soil_Temperature::~Sensor_Soil_Temperature() {}
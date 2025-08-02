#include <Sensor_Soil_Temperature.h>

Sensor_Soil_Temperature::Sensor_Soil_Temperature(uint8_t pin, std::string topic) : oneWire(pin),
                                                                                   sensors(&oneWire),
                                                                                   temperature(404), topic(topic), isconnected(false)
{
    metricValues[Metric_Type::SOIL_TEMPERATURE] = "0";
};

bool Sensor_Soil_Temperature::initialize()
{   
    if(!isconnected){
        sensors.begin();
    }else{
        DeviceAddress deviceAddress;
        isconnected = sensors.isConnected(deviceAddress);
        mqttdebug("ADS1015 nicht verbunden");
    }
    return isconnected;
}

void Sensor_Soil_Temperature::readValue()
{
    if(isconnected){
        isconnected = true;
        sensors.requestTemperatures();

        temperature = sensors.getTempCByIndex(0);

        if (temperature == DEVICE_DISCONNECTED_C)
        {
            mqttdebug("ADS1015 nicht verbunden");
        }

        metricValues[Metric_Type::SOIL_TEMPERATURE] = temperature;
    }else{
        isconnected = false;
    }
}

void Sensor_Soil_Temperature::sendMqttMessage()
{
    sendmqttmessage(metricValues.at(Metric_Type::SOIL_TEMPERATURE), topic);
}

Sensor_Soil_Temperature::~Sensor_Soil_Temperature() {}
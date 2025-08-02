#include <OneWire.h>
#include <DallasTemperature.h>
#include "Sensor_abstract.h"
#include "mqtt.h"
#include "Metric_Type.h"

class Sensor_Soil_Temperature : public Sensor_abstract {
    private: 
        OneWire oneWire;
        DallasTemperature sensors;
        float temperature;
        std::string topic;
        bool isconnected;
    
    public:
        Sensor_Soil_Temperature() {};    
        Sensor_Soil_Temperature(uint8_t pin, std::string topic);
        bool initialize() override;
        void readValue() override;
        void sendMqttMessage() override;

        ~Sensor_Soil_Temperature();
};
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
    
    public:
        Sensor_Soil_Temperature() {};    
        Sensor_Soil_Temperature(uint8_t pin);
        void initialize() override;
        std::map<Metric_Type, std::string> readValue() override;
        void sendMqttMessage() override;

        ~Sensor_Soil_Temperature();
};
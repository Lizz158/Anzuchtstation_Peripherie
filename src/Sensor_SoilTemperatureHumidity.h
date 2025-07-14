# include <OneWire.h>
# include <DallasTemperature.h>

class Sensor_SoilTemperatureHumidity{
    private: 
        OneWire oneWire;
        DallasTemperature sensors;
        float temperature;
    
    public:
        Sensor_SoilTemperatureHumidity(uint8_t pin);
        float getreading();
};
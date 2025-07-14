# include <OneWire.h>
# include <DallasTemperature.h>

class sensorBodentemp{
    private: 
        OneWire oneWire;
        DallasTemperature sensors;
        float temperature;
    
    public:
        sensorBodentemp(uint8_t pin);
        float getreading();
};
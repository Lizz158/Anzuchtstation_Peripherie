# include <Sensor_SoilTemperatureHumidity.h>

Sensor_SoilTemperatureHumidity::Sensor_SoilTemperatureHumidity(uint8_t pin) : oneWire(pin), sensors(&oneWire), temperature(404){
    sensors.begin();
}

float Sensor_SoilTemperatureHumidity::getreading(){
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    if(temperature == DEVICE_DISCONNECTED_C){
        return 404;
    }
    return temperature;
}
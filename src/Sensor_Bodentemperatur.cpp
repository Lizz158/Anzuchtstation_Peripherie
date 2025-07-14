# include <Sensor_Bodentemperatur.h>

sensorBodentemp::sensorBodentemp(uint8_t pin) : oneWire(pin), sensors(&oneWire), temperature(404){
    sensors.begin();
}

float sensorBodentemp::getreading(){
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    if(temperature == DEVICE_DISCONNECTED_C){
        return 404;
    }
    return temperature;
}
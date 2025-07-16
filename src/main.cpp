#include "wlan.h"
#include "mqtt.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Sensor_Soil_Temperature.h"
#include "Sensor_Soil_Humidity.h"
#include "Sensor_Room.h"

Sensor_Room* pSensorRoom;
Sensor_Soil_Temperature* pSensorSoilTemperature;
Sensor_Soil_Humidity* pSensorSoilHumidity;

void setup() {
  pSensorRoom = new Sensor_Room;
  pSensorSoilTemperature = new Sensor_Soil_Temperature;
  pSensorSoilHumidity = new Sensor_Soil_Humidity;
  
  Serial.begin(115200);
  while (!Serial);
  
  startwlan();
  
  startmqtt();
  
  pSensorRoom->initialize();

  pSensorSoilTemperature->initialize();
}

void loop() {

  std::map<Metric_Type, std::string> SensorRoom_Values = pSensorRoom->readValue();
  pSensorRoom->sendMqttMessage();

  std::map<Metric_Type, std::string> SensorSoilTemperature_Values = pSensorSoilTemperature->readValue();
  pSensorSoilTemperature->sendMqttMessage();

  std::map<Metric_Type, std::string> SensorSoilHumidity_Values = pSensorSoilHumidity->readValue();
  pSensorSoilHumidity->sendMqttMessage();
}
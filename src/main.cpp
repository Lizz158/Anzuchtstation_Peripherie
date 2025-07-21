#include "wlan.h"
#include "mqtt.h"
#include <Wire.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Sensor_Soil_Temperature.h"
#include "Sensor_Soil_Humidity.h"
#include "Sensor_Room.h"
#include "Actor_Lamp.h"

Sensor_Room* pSensorRoom;
Sensor_Soil_Temperature* pSensorSoilTemperature;
Sensor_Soil_Humidity* pSensorSoilHumidity;
Actor_Lamp* pActorLampUp;

void setup() {
  // pSensorRoom = new Sensor_Room;
  // pSensorSoilTemperature = new Sensor_Soil_Temperature(D5);
  // pSensorSoilHumidity = new Sensor_Soil_Humidity;
  pActorLampUp = new Actor_Lamp("anzuchtstation/lampe_oben", D6, 0);

  pinMode(D6, OUTPUT);
  // digitalWrite(D2, LOW);
  
  Serial.begin(115200);
  while (!Serial);

  Wire.begin();               // I2C-Pins definieren
  
  startwlan();
  
  startmqtt();
  
  // pSensorRoom->initialize();

  // pSensorSoilTemperature->initialize();

  subscribetopics();

}

void loop() {

  mqttloop();

  // std::map<Metric_Type, std::string> SensorRoom_Values = pSensorRoom->readValue();
  // pSensorRoom->sendMqttMessage();

  // std::map<Metric_Type, std::string> SensorSoilTemperature_Values = pSensorSoilTemperature->readValue();
  // pSensorSoilTemperature->sendMqttMessage();

  // std::map<Metric_Type, std::string> SensorSoilHumidity_Values = pSensorSoilHumidity->readValue();
  // pSensorSoilHumidity->sendMqttMessage();
}
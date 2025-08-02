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


Sensor_Room *pSensorRoom;
Sensor_Soil_Temperature *pSensorSoilTemperature;
Sensor_Soil_Humidity *pSensorSoilHumidity0;
Sensor_Soil_Humidity *pSensorSoilHumidity1;
Sensor_Soil_Humidity *pSensorSoilHumidity2;
Actor_Lamp *pActorLampUp;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  // pSensorRoom = new Sensor_Room;
  // pSensorSoilTemperature = new Sensor_Soil_Temperature(D5);
  pSensorSoilHumidity0 = new Sensor_Soil_Humidity(0.96, 2.67, 0);
  pSensorSoilHumidity1 = new Sensor_Soil_Humidity(0.96, 2.67, 1);
  pSensorSoilHumidity2 = new Sensor_Soil_Humidity(0.96, 2.67, 2);
  pActorLampUp = new Actor_Lamp("anzuchtstation/lampe_oben", D6, 0);


  Wire.begin(); // I2C-Pins definieren

  startwlan();

  startmqtt();

  subscribetopics();

}

void loop()
{

  mqttloop();

  // std::map<Metric_Type, std::string> SensorRoom_Values = pSensorRoom->readValue();
  // pSensorRoom->sendMqttMessage();

  // std::map<Metric_Type, std::string> SensorSoilTemperature_Values = pSensorSoilTemperature->readValue();
  // pSensorSoilTemperature->sendMqttMessage();

  std::map<Metric_Type, std::string> SensorSoilHumidity_Values0 = pSensorSoilHumidity0->readValue();
  pSensorSoilHumidity0->sendMqttMessage();
  std::map<Metric_Type, std::string> SensorSoilHumidity_Values1 = pSensorSoilHumidity1->readValue();
  pSensorSoilHumidity1->sendMqttMessage();
  std::map<Metric_Type, std::string> SensorSoilHumidity_Values2 = pSensorSoilHumidity2->readValue();
  pSensorSoilHumidity2->sendMqttMessage();

  delay(1000);
}
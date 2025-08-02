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
#include "Sensor_Light.h"
#include "Actor_HeatingMat.h"

Sensor_Room *pSensorRoom;
Sensor_Light *pSensorLight;
Sensor_Soil_Temperature *pSensorSoilTemperature0;
Sensor_Soil_Temperature *pSensorSoilTemperature1;
Sensor_Soil_Temperature *pSensorSoilTemperature2;
Sensor_Soil_Humidity *pSensorSoilHumidity0;
Sensor_Soil_Humidity *pSensorSoilHumidity1;
Sensor_Soil_Humidity *pSensorSoilHumidity2;
Actor_Lamp *pActorLampUp0;
Actor_Lamp *pActorLampUp1;
Actor_Lamp *pActorLampUp2;
Actor_HeatingMat *pActor_HeatingMat0;
Actor_HeatingMat *pActor_HeatingMat1;
Actor_HeatingMat *pActor_HeatingMat2;
bool blink = true;

void setup()
{
  // Serial.begin(115200);
  // while (!Serial);
  
  startwlan();
  startmqtt();
  
  Wire.begin(); // I2C-Pins definieren
  
  pSensorRoom = new Sensor_Room;
  pSensorLight = new Sensor_Light;

  pSensorSoilTemperature0 = new Sensor_Soil_Temperature(D0, "bodentemperatur_oben");
  pSensorSoilTemperature1 = new Sensor_Soil_Temperature(D3, "bodentemperatur_mitte");
  pSensorSoilTemperature2 = new Sensor_Soil_Temperature(D4, "bodentemperatur_unten");

  pSensorSoilHumidity0 = new Sensor_Soil_Humidity(0.96, 2.67, 0, "bodenfeuchtigkeit_oben");
  pSensorSoilHumidity1 = new Sensor_Soil_Humidity(0.96, 2.67, 1, "bodenfeuchtigkeit_mitte");
  pSensorSoilHumidity2 = new Sensor_Soil_Humidity(0.96, 2.67, 2, "bodenfeuchtigkeit_unten");
  
  pActorLampUp0 = new Actor_Lamp("anzuchtstation/lampe_oben", D5, 0);
  pActorLampUp1 = new Actor_Lamp("anzuchtstation/lampe_mitte", D6, 0);
  pActorLampUp2 = new Actor_Lamp("anzuchtstation/lampe_unten", D7, 0);

  pActor_HeatingMat0 = new Actor_HeatingMat("anzuchtstation/heizmatte_oben", D8, 0);
  // pActor_HeatingMat1 = new Actor_HeatingMat("anzuchtstation/heizmatte_mitte", D9, 0);
  // pActor_HeatingMat2 = new Actor_HeatingMat("anzuchtstation/heizmatte_unten", D10, 0);

  subscribetopics();
}

void loop()
{
  mqttloop();
  // Serial.println(1);
  
  if (pSensorRoom->initialize())
  {
    pSensorRoom->readValue();
    pSensorRoom->sendMqttMessage();
  }
  // Serial.println(2);
  
  if (pSensorLight->initialize())
  {
    pSensorLight->readValue();
    pSensorLight->sendMqttMessage();
  }
  // Serial.println(3);
  
  if (pSensorSoilTemperature0->initialize())
  {
    pSensorSoilTemperature0->readValue();
    pSensorSoilTemperature0->sendMqttMessage();
  }
  // Serial.println(4);
  
  if (pSensorSoilTemperature1->initialize())
  {
    pSensorSoilTemperature1->readValue();
    pSensorSoilTemperature1->sendMqttMessage();
  }
  // Serial.println(5);
  
  if (pSensorSoilTemperature2->initialize())
  {
    pSensorSoilTemperature2->readValue();
    pSensorSoilTemperature2->sendMqttMessage();
  }
  // Serial.println(6);
  
  if (pSensorSoilHumidity0->initialize())
  {
    pSensorSoilHumidity0->readValue();
    pSensorSoilHumidity0->sendMqttMessage();
  }
  // Serial.println(7);
  
  if (pSensorSoilHumidity1->initialize())
  {
    pSensorSoilHumidity1->readValue();
    pSensorSoilHumidity1->sendMqttMessage();
  }

  if (pSensorSoilHumidity2->initialize())
  {
    pSensorSoilHumidity2->readValue();
    pSensorSoilHumidity2->sendMqttMessage();
  }
}
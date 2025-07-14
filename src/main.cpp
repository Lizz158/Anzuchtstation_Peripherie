#include "wlan.h"
#include "mqtt.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Sensor_Bodentemperatur.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
bool bme_connected = false;

#define pin_bodentemperatur1 12
sensorBodentemp Bodentemperatur1(pin_bodentemperatur1);

const long dryVal1 = 800;
const long wetVal1 = 300;

Adafruit_BME680 bme(&Wire); // I2C

void setup() {
  Serial.begin(115200);
  while (!Serial);
  startwlan();
  startmqtt();

  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    bme_connected = false;
  }else{
    bme_connected = true;
  }

  if(bme_connected){
    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
  }
  //pinMode(D7, INPUT);
}

void loop() {
  if(bme_connected){
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      return;
    }
    std::string raumtemperatur = std::to_string(bme.temperature);
    sendmqttmessage(raumtemperatur, "raumtemperatur");

    Serial.print("Temperature = ");
    Serial.print(bme.temperature);
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bme.pressure / 100.0);
    Serial.println(" hPa");

    Serial.print("Humidity = ");
    Serial.print(bme.humidity);
    Serial.println(" %");

    Serial.print("Gas = ");
    Serial.print(bme.gas_resistance / 1000.0);
    Serial.println(" KOhms");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.println();
  }
  std::string bodentemperature1 = std::to_string(Bodentemperatur1.getreading());
  sendmqttmessage(bodentemperature1, "bodentemperatur1");
  delay(2000);


  int a = analogRead(A0);
  long humidity = map(a, wetVal1, dryVal1, 100, 0);
  // Serial.println(voltage);
  Serial.println(humidity);
}
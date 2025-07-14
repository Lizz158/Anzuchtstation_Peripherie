#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

// #define SEALEVELPRESSURE_HPA (1013.25)

// Adafruit_BME680 bme(&Wire); // I2C

class BME680{
    private:
        float temperature;
        float humidity;
    public:
        BME680();
};
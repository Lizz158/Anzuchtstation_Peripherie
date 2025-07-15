
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <Wire.h>
#include "Sensor_abstract.h"
#include "mqtt.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

class Sensor_Room : public Sensor_abstract {
    private:
        float temperature;
        float humidity;
        Adafruit_BME680 bme; // I2C
        bool bme_connected;

    public:
        Sensor_Room();
        void initialize() override;
        std::map<Metric_Type, std::string> readValue() override;

        ~Sensor_Room();
};
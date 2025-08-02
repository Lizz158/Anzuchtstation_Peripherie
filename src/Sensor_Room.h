
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Sensor_abstract.h"
#include "mqtt.h"
#include "Metric_Type.h"

class Sensor_Room : public Sensor_abstract {
    private:
        float temperature;
        float humidity;
        Adafruit_BME680 bme; // I2C
        bool bme_connected;

    public:
        Sensor_Room();
        bool initialize() override;
        void readValue() override;
        void sendMqttMessage() override;

        ~Sensor_Room();
};
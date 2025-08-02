#include "Sensor_abstract.h"
#include "mqtt.h"
#include "Metric_Type.h"
#include <Adafruit_ADS1X15.h>

class Sensor_Soil_Humidity : public Sensor_abstract {
    private:
        // Values for dry and wet sensor
        double dryVal;
        double wetVal;
        // Kanal für Analogeingang
        uint8_t channel;
        static Adafruit_ADS1015 ads;
        static bool isadsinitialized;

    public:
        Sensor_Soil_Humidity(double dryVal, double wetVal, uint8_t channel);
        void initialize() override;
        std::map<Metric_Type, std::string> readValue() override;
        void sendMqttMessage() override;
        ~Sensor_Soil_Humidity();    
};
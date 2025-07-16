#include "Sensor_abstract.h"
#include "mqtt.h"
#include "Metric_Type.h"

class Sensor_Soil_Humidity : public Sensor_abstract {
    private:
        // Values for dry and wet sensor
        const long dryVal = 800;
        const long wetVal = 300;

    public:
        Sensor_Soil_Humidity();
        void initialize() override;
        std::map<Metric_Type, std::string> readValue() override;
        void sendMqttMessage() override;

        ~Sensor_Soil_Humidity();    
};
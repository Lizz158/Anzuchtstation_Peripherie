
#include "Sensor_abstract.h"
#include "mqtt.h"
#include "Metric_Type.h"
#include <hp_BH1750.h>

class Sensor_Light : public Sensor_abstract
{
private:
    hp_BH1750 BH1750;
    float light;
    bool isconnected;

public:
    Sensor_Light();
    bool initialize() override;
    void readValue() override;
    void sendMqttMessage() override;

    ~Sensor_Light();
};
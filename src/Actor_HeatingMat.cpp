#include <Actor_HeatingMat.h>

/**
 * @brief Construct a new Actor_HeatingMat::Actor_HeatingMat object
 *
 * @param topic The MQTT Topic that calls the callback function for the HeatingMat
 * @param relaisPin Pin of the relays that turns the HeatingMat on and off
 * @param analogOutputPin Pin on the Analog Output card that dims the HeatingMat
 */
Actor_HeatingMat::Actor_HeatingMat(std::string topic, uint8_t relaisPin, uint8_t analogOutputPin)
    : topic(topic), relaisPin(relaisPin), analogOutputPin(analogOutputPin)
{
    addCallback(topic);
    pinMode(relaisPin, OUTPUT);
    digitalWrite(relaisPin, HIGH); // High: Aus, Low: Ein. HeatingMat ist standardmäßig ausgeschalten.
};

/**
 * @brief Callback function of the HeatingMat. Operates HeatingMat through the Analog Output card.
 *
 * @param message The MQTT message of the topic that calls this callback function.
 */
void Actor_HeatingMat::setOutputs(std::string message)
{

    if (message.compare("ON") == 0)
    {
        digitalWrite(relaisPin, LOW); // FIXME: HeatingMat geht nicht an, wenn sie vorher aus war
        mqttdebug(message);
        return;
    }
    else
    {
        percentage = 0;
        digitalWrite(relaisPin, HIGH);
        mqttdebug(message);
        return;
    }
}

Actor_HeatingMat::~Actor_HeatingMat() {};
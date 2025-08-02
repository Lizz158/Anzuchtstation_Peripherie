#include <Actor_Lamp.h>

/**
 * @brief Define the I2C Adress of the Analog Output card as 7 Bit (all jumpers down)
 *
 */
#define I2C_AOUT_ADDR 176 >> 1 // I2C-Addresse der analogen Ausgangskarte definieren )als 7 Bit (Alle Jumper unten))

/**
 * @brief Construct a new Actor_Lamp::Actor_Lamp object
 *
 * @param topic The MQTT Topic that calls the callback function for the lamp
 * @param relaisPin Pin of the relays that turns the lamp on and off
 * @param analogOutputPin Pin on the Analog Output card that dims the lamp
 */
Actor_Lamp::Actor_Lamp(std::string topic, uint8_t relaisPin, uint8_t analogOutputPin)
    : topic(topic), relaisPin(relaisPin), analogOutputPin(analogOutputPin)
{
    addCallback(topic);
    pinMode(relaisPin, OUTPUT);
    digitalWrite(relaisPin, HIGH); // High: Aus, Low: Ein. Lampe ist standardmäsig ausgeschalten.
};

/**
 * @brief Callback function of the lamp. Operates lamp through the Analog Output card.
 *
 * @param message The MQTT message of the topic that calls this callback function.
 */
void Actor_Lamp::setOutputs(std::string message)
{
    if (message.compare("OFF") == 0)
    {
        percentage = 0;
        digitalWrite(relaisPin, HIGH);
    }
    else if (message.compare("ON") == 0)
    {
        digitalWrite(relaisPin, LOW); // FIXME: Lampe geht nicht an, wenn sie vorher aus war
        return;
    }
    else
    {
        try
        {
            percentage = std::stoi(message);
        }
        catch (int e)
        {
            mqttdebug(std::to_string(e));
        }
    }

    /**
     * @brief Map 255 bits to 100% and 0 bits to 0%
     *
     */
    percentage = int(map(percentage, 255, 0, 100, 0));

    byte LBy = 0;
    byte HBy = 0;

    /**
     * @brief (percentage * 10) because 1% is 10
     *
     */
    HBy = (percentage * 10) / 256;
    LBy = (percentage * 10) - HBy * 256;

    Wire.beginTransmission(I2C_AOUT_ADDR);
    Wire.write(analogOutputPin);
    Wire.write(LBy);
    Wire.write(HBy);
    int error = Wire.endTransmission();
    if (error>0){
        mqttdebug(topic + " " + std::to_string(error));
    }
};

Actor_Lamp::~Actor_Lamp() {};
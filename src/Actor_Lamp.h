#include <Actor_abstract.h>
#include <Wire.h>

/**
 * @brief Class for lamps
 * 
 * @param percentage The percentage for dimming the lamp
 */
class Actor_Lamp : public Actor_abstract {
    private:
        int percentage = 0;
        std::string topic;
        uint8_t relaisPin;
        uint8_t analogOutputPin;
        

    public:
        Actor_Lamp(std::string topic, uint8_t relaisPin, uint8_t analogOutputPin);
        void setOutputs(std::string message) override;
        ~Actor_Lamp();
};
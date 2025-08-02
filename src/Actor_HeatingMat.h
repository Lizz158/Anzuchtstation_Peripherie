#include <Actor_abstract.h>
#include <Wire.h>

/**
 * @brief Class for HeatingMats
 * 
 * @param percentage The percentage for dimming the HeatingMat
 */
class Actor_HeatingMat : public Actor_abstract {
    private:
        int percentage = 0;
        std::string topic;
        uint8_t relaisPin;
        uint8_t analogOutputPin;
        

    public:
        Actor_HeatingMat(std::string topic, uint8_t relaisPin, uint8_t analogOutputPin);
        void setOutputs(std::string message) override;
        ~Actor_HeatingMat();
};
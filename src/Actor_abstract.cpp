#include <Actor_abstract.h>

/**
 * @brief Add a new topic with its callback function to the map Callbackmap
 * 
 * @param topic The topic that triggers the callback function
 */
void Actor_abstract::addCallback(std::string topic) {
    std::function<void(std::string)> callback = std::bind(&Actor_abstract::setOutputs, this, std::placeholders::_1);
    Callbackmap[topic] = callback;
};
#pragma once
#include <mqtt.h>

/**
 * @brief Abstract class for actors
 * 
 */
class Actor_abstract {
    
    protected:

        void addCallback(std::string topic);    
    
        virtual void setOutputs(std::string message) = 0;

        virtual ~Actor_abstract(){};
};
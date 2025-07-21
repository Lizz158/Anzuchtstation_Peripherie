#include "mqtt.h"

WiFiClient wlanClient;
PubSubClient mqttClient(wlanClient);
std::map<std::string, std::function<void(std::string)>> Callbackmap;

void callback(char* topic, byte* message, unsigned int length) {
    // Serial.println(topic);
    std::string messageString((char*)message, length);
    Callbackmap.at(std::string(topic))(messageString);
}

void startmqtt(){
    mqttClient.setServer ("192.168.188.39",1883);
    if(mqttClient.connect ("ESP-Client","mqtt_plantcontroller","machhaltirgendwas")) {
        Serial.println ("Connected to MQTT Broker");
        mqttClient.setCallback(callback);
    } else {
        Serial.println("MQTT Broker connection failed");
        Serial.println (mqttClient.state());
        delay(200);
    }
}

void sendmqttmessage(std::string message, std::string topic){
    std::string maintopic("anzuchtstation/");
    maintopic += topic;
    mqttClient.publish(maintopic.c_str(), message.c_str());
}

void subscribetopics(){
    for (auto const& pair : Callbackmap) {
        auto key = pair.first;
        // mqttClient.subscribe(key.c_str());"anzuchtstation/lampe_oben"
        mqttClient.subscribe("anzuchtstation/lampe_oben");
    }
}

void mqttloop(){
    mqttClient.loop();
}
#include "mqtt.h"

WiFiClient wlanClient;
PubSubClient mqttClient(wlanClient);

void startmqtt(){
    mqttClient.setServer ("192.168.188.39",1883);
    if(mqttClient.connect ("ESP-Client","mqtt_plantcontroller","machhaltirgendwas")) {
        Serial.println ("Connected to MQTT Broker");
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
    Serial.println(maintopic.c_str());
    Serial.println(message.c_str());
}
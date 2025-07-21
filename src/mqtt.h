#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <bits/stdc++.h>

extern std::map<std::string, std::function<void(std::string)>> Callbackmap;

void startmqtt();
void sendmqttmessage(std::string message, std::string topic);
void addcallback(const std::function<void(char* topic, byte* message, int length)>& callback, std::string topic);
void subscribetopics();
void mqttloop();
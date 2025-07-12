#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <bits/stdc++.h>

void startmqtt();
void sendmqttmessage(std::string message, std::string topic);
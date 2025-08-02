#include "wlan.h"

const char *ssid = "FRITZ!Box 24GHz";
const char *password = "81432520353455115199";

void startwlan(){
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    // Serial.print("*");
  }  
  // Serial.println("success!");
  // Serial.print("IP Address is: ");
  // Serial.println(WiFi.localIP());
  // Serial.println("WLAN verbunden!");
}
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// const char *ssid = "FRITZ!Box 24GHz";
// const char *password = "81432520353455115199";
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print("Not working");
//   }
#include <Wire.h>
 
void setup()
{
  Serial.begin(115200);
  Wire.begin();
}
 
void loop() 
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
      { Serial.print("0"); }
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
      { Serial.print("0"); }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
  { Serial.println("No I2C devices found\n"); }
  else
  { Serial.println("done\n"); }
 
  delay(5000);           // wait 5 seconds for next scan
}
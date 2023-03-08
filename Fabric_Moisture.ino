//Program to upload Moisture percentage to Ubidots IoT cloud(HTTP) and NodeMcu//
#include "Ubidots.h" 

const char* UBIDOTS_TOKEN = "      ";  // set your Ubidots TOKEN here
const char* WIFI_SSID = "        ";      // set your Wi-Fi SSID here
const char* WIFI_PASS = "       ";      // set your Wi-Fi password here
const int sensor_pin = A0;
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
  
void setup() 
{
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  Serial.println("NodeMCU Meets Ubidots");
  delay(1000);
  Serial.println("Sensor Initializing... Please Wait....");
  delay(2000);
}

void loop() 
{
  float moisture_percentage;
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
  Serial.print("Fabric Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  //Create variable to upload the moisture percentage on cloud
  ubidots.add("Moisture Percentage", moisture_percentage);  
   
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Use send function to send data with device label that matches the device Id

  if (bufferSent) 
  {
   Serial.println("Values sent by the device");
  }
  delay(5000);
}

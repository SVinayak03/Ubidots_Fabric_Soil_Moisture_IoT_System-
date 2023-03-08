#include "Ubidots.h" 
#include <DHT.h>

#define PIN 4
#define DHT_TYPE DHT11

DHT dht(PIN,DHT_TYPE);
float t,h;

const char* UBIDOTS_TOKEN = "BBFF-iRJCQAMMMmbIgDVPuFAkdUV8tGZSkh";  // Put your Ubidots TOKEN here
const char* WIFI_SSID = "Realme 5 pro";      // Put your Wi-Fi SSID here
const char* WIFI_PASS = "12345678";      // Put your Wi-Fi password here

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
  
void setup() 
{
  dht.begin();
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // This is only for developers & testers to debug the process  
  Serial.println("NodeMCU Meets Ubidots");
  delay(1000);
  Serial.println("Sensor Initializing... Please Wait....");
  delay(2000);
}

void loop() 
{
  //read sensor values
  t = dht.readTemperature();
  h = dht.readHumidity();

  Serial.println("Temp = "+String(t)+"\t Humidity = "+String(h)+"");
  
  //Create variables for sending on server & assign them sensor returned values
  ubidots.add("temperature", t);  
  ubidots.add("humidity", h);
 
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

  if (bufferSent) 
  {
   Serial.println("Values sent by the device");
  }
  delay(5000);
}

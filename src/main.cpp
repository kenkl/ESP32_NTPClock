#include <Arduino.h>
#include <SPI.h> // Don't strictly need this, but PIO chokes if it's not included here.
#include <Wifi.h>
#include <WiFiClient.h>
#include "Adafruit_LEDBackpack.h"
#include <Wire.h>
#include "time.h"

// put the WIFI credentials in wificreds.h, in the same directory as buttonthing.cpp (this file) with the lines:
// const char* ssid = "WIFI SSID";
// const char* password = "WIFI SECRET PASSWORD";
// (uncommented, of course)
#include "wificreds.h"

unsigned int myMins = 0;
unsigned int myHRs = 0;
unsigned int brightness = 3;
unsigned int secsElapsed = 0;

// Grab the time from this server:
const char* ntpServer = "time.apple.com";

/* GMT offset (in seconds)
   For UTC -5.00 : -5 * 60 * 60 : -18000
   For UTC +1.00 : 1 * 60 * 60 : 3600
   For UTC +0.00 : 0 * 60 * 60 : 0
*/
const long gmtOffset_sec = -18000; // EST

// DST offset (on or off really...)
//const int daylightOffset_sec = 3600;
const int daylightOffset_sec = 0;


const int led=13;
Adafruit_7segment matrix = Adafruit_7segment();

void updateDisplay(int myHRs, int myMins);
void printLocalTime();

void setup() {
  pinMode(led, OUTPUT);
  matrix.begin(0x70);
  Serial.begin(115200);
  digitalWrite(led, 1);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // Set ESP to be a WiFi client 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  
  Serial.println();
  Serial.println();
  Serial.println("ESP32_NTPClock - 2020-01-19");
  Serial.println("Screw you Ahmed, you poser.");
  Serial.println();
  digitalWrite(led, 0);

}

void loop() {
  secsElapsed = millis() / 1000;

  // Leftover diagnostic code - simply displays the time elapsed since power-on.
  //myMins = secsElapsed / 60;
  //myHRs = myMins / 60;
  //updateDisplay(myHRs, myMins);
  
  delay(1000);
  printLocalTime();
  
}

void updateDisplay(int myHRs, int myMins){

  // Let's force leading zeros and write the display - WARNING: remember the numbering scheme - 0,1,3,4 
  if(myHRs < 10) matrix.writeDigitNum(0, 0);
  else{
    matrix.writeDigitNum(0, (myHRs / 10));
  }
  matrix.writeDigitNum(1, (myHRs % 10));
  
  if(myMins < 10) matrix.writeDigitNum(3, 0); 
  else {
    matrix.writeDigitNum(3, (myMins / 10));
  }
  matrix.writeDigitNum(4, (myMins % 10));

  if(secsElapsed % 2 !=0) matrix.drawColon(false);
  else matrix.drawColon(true);
  matrix.writeDisplay();

}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  updateDisplay(timeinfo.tm_hour, timeinfo.tm_min);
}

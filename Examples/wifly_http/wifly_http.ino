
 
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFly.h>
#include "HTTPClient.h"

#define SSID      "Seed"
#define KEY       "link2world"
#define AUTH      WIFLY_AUTH_WPA2_PSK

//#define HTTP_GET_URL "http://httpbin.org/get?hello=world"
#define HTTP_GET_URL "http://baidu.com/"
#define HTTP_POST_URL "http://httpbin.org/post"
#define HTTP_POST_DATA "Hello world!"

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
WiFly wifly(2, 3);
HTTPClient http;

void setup() {
  Serial.begin(9600);
  Serial.println("------- WIFLY HTTP --------");
  
  // Wait WiFly to init
//  delay(3000);
  
//  wifly.reset();

  while (1) {
    Serial.println("Try to join " SSID );
    if (wifly.join(SSID, KEY, AUTH)) {
      Serial.println("Succeed to join " SSID);
      wifly.clear();
      break;
    } else {
      Serial.println("Failed to join " SSID);
      Serial.println("Wait 1 second and try again...");
      delay(1000);
    }
  }
  
   while (http.get(HTTP_GET_URL, 10000) < 0) {
     delay(1000);
   }
   
   char get;
   
   while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
     Serial.print(get);
   }
   
   while (http.post(HTTP_POST_URL, HTTP_POST_DATA, 10000) < 0) {
     delay(1000);
   }
   
   while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
     Serial.print(get);
   }
   
   if (wifly.commandMode()) {
    Serial.println("\r\nEnter command mode. Send \"exit\"(with \\r) to exit command mode");
   }
}


void loop() {
  int c;
  while (wifly.available()) {
    c = wifly.read();
    if (c > 0) {
      Serial.write((char)c);
    }
  }
  
  while (Serial.available()) {
    c = Serial.read();
    if (c >= 0) {
      wifly.write((char)c);
    }
  }
}
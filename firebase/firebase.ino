#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
//
//#include <FirebaseJson.h>
//#include <jsmn.h>

//#include <BearSSLHelpers.h>
//#include <CertStoreBearSSL.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266WiFiAP.h>
//#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266WiFiScan.h>
//#include <ESP8266WiFiSTA.h>
//#include <ESP8266WiFiType.h>
//#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
//#include <WiFiClientSecureAxTLS.h>
//#include <WiFiClientSecureBearSSL.h>
//#include <WiFiServer.h>
//#include <WiFiServerSecure.h>
//#include <WiFiServerSecureAxTLS.h>
//#include <WiFiServerSecureBearSSL.h>
//#include <WiFiUdp.h>


#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>
 
// Set these to run example.
#define FIREBASE_HOST "https://arduino-666d9.firebaseio.com/"
#define FIREBASE_AUTH "GfomCEriYbDOVWnxFS2mw37Zc0wS5oXHXigLAv6a"
#define WIFI_SSID "Amsa Net"
#define WIFI_PASSWORD "marakhatui"
 
String myString;
int vr = A0; // variable resistor connected 
int sdata = 0; // The variable resistor value will be stored in sdata.
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(vr ,INPUT);
  // connect to wifi.
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
   Firebase.setString("Variable/Value","fahad");
}
 
void loop()
{
 
//sdata = analogRead(vr);
//myString = String(sdata); 
//Serial.println(myString); 
Firebase.setString("Variable/Value","66");
delay(1000);            
}

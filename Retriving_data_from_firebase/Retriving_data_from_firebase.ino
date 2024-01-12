///////////////ustudent___arduino
#include "FirebaseArduino.h"
#include <ESP8266WiFi.h>
//#define WIFI_SSID "CUET--Students"
//#define WIFI_PASSWORD "1020304050"
#define WIFI_SSID "iPhone Amsa"
#define WIFI_PASSWORD "99999999"
#define FIREBASE_HOST "arduino-666d9.firebaseio.com" 
#define FIREBASE_AUTH "GfomCEriYbDOVWnxFS2mw37Zc0wS5oXHXigLAv6a"
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
String a;
char s[200];
void loop() {
  a= Firebase.getString("Medicine/46MZTkl7LgQCS1K2DoXCeMkPJ802/Morning");
  if(Firebase.failed()){
    Serial.println(Firebase.error());
    }
    else{
      Serial.print("Morning: ");
      Serial.println(a);
          int i = 0; //start at 0
          do {
              s[i] = (a)[i]; //assign s[i] to the string literal index i
          } while(s[i++]);
//          Serial.write("Morning: ");
//          Serial.write(s);
          }
  delay(1000);

  a= Firebase.getString("Medicine/46MZTkl7LgQCS1K2DoXCeMkPJ802/Noon");
  if(Firebase.failed()){
    Serial.println("rtet"+Firebase.error());
    }
    else{
      Serial.print("Noon: ");
      Serial.println(a);
            int i = 0; //start at 0
            do {
                s[i] = (a)[i]; //assign s[i] to the string literal index i
            } while(s[i++]);
//            Serial.write("Noon: ");
//            Serial.write(s);
            
      }
  delay(1000);

  a= Firebase.getString("Medicine/46MZTkl7LgQCS1K2DoXCeMkPJ802/Night");
  if(Firebase.failed()){
    Serial.println(Firebase.error());
    }
    else{
      Serial.print("Night: ");
      Serial.println(a);
          int i = 0; //start at 0
          do {
              s[i] = (a)[i]; //assign s[i] to the string literal index i
          } while(s[i++]);
//          Serial.write("Night: ");
//          Serial.write(s);
          
      }
  delay(1000);

  /*a= Firebase.getString("Amsa/a");
  if(Firebase.failed()){
    Serial.println(Firebase.error());
    Serial.print("Objecjjjt: ");
    }
    else{
      Serial.print("Object: ");
      Serial.println(a);
      }*/
//  delay(5000);




  
//  a= Firebase.getString("logs/num");
////  Serial.println(a);
//  if(Firebase.failed()){
//    Serial.println(Firebase.error());
//    }
//    else{
//      Serial.println(a);
//      }
//  delay(100);
  
}

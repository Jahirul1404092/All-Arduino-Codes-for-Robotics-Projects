
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#define WIFI_SSID "iPhone Amsa"
#define WIFI_PASSWORD "99999999"
#define FIREBASE_HOST "https://push-c6f5b.firebaseio.com/" 
#define FIREBASE_AUTH "qZZ2osvT5mflV86QBzgPQQYACyRuRoV6xaNtvISs"
#define FIREBASE_FCM_SERVER_KEY "AAAAwQfO-nw:APA91bFJGymr65yIHIfqziVD52D3MR91LStQ6y-MVB2v-QGbwiKRHGH9dfb37SfuCq4WbmWJt3yTygCOsYoCDGNeFRnF7aljI1QpsxvPk7kJ9TBbEexxdTcGs8hRTW07_GBmwNYRLfAE"
#define FIREBASE_FCM_DEVICE_TOKEN_1 "eFXLRUCHc1M:APA91bEyYVPnfWofNUFm_13_upN_nE3XSadoB4Yyaw_LPT4qvR0wt1orl02PR-vj3bqVZXy2ktZZj0BOvyTQFfX_yQQbPk0p9GbI_T4y795b5G56aIBHrEHIcV9n3DYWrGZn6RwGOYh3"
FirebaseData firebaseData1;
unsigned long lastTime = 0;
int count = 0;
void sendMessage();
double latt=0.0;
double lon=0.0;
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
static const int RXPin = D4, TXPin = D3;
static const uint32_t GPSBaud = 9600;

int buzzer = D1;
int LED = D0;
int flame_sensor = A0;

SoftwareSerial ss(RXPin, TXPin);
int flame_value;

void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    firebaseData1.fcm.begin(FIREBASE_FCM_SERVER_KEY);

    firebaseData1.fcm.addDeviceToken(FIREBASE_FCM_DEVICE_TOKEN_1);

//    firebaseData1.fcm.addDeviceToken(FIREBASE_FCM_DEVICE_TOKEN_2);

    firebaseData1.fcm.setPriority("high");

    firebaseData1.fcm.setTimeToLive(1000);

//    sendMessage();

    pinMode(buzzer, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(flame_sensor, INPUT);

    ss.begin(GPSBaud);
}

void loop()

{/*
  sendMessage();
  Serial.println("-");
      while (ss.available() > 0){
        gps.encode(ss.read());
        if (gps.location.isUpdated()){
          Serial.print("Latitude= "); 
          latt=gps.location.lat(), 6;
          Serial.print(latt);
          Serial.print(" Longitude= "); 
          lon=gps.location.lng(), 6;
          Serial.println(lon);

          flame_value=analogRead(flame_sensor);
          Serial.println(flame_value);
          
          if(flame_value<200){
            Serial.println("Flame detected...! take action immediately.");
            digitalWrite(buzzer, HIGH);
            digitalWrite(LED, HIGH);
            delay(200);
            digitalWrite(buzzer, LOW);
            digitalWrite(LED, LOW);
            delay(50);
            sendMessage();
            }else
          {
            Serial.println("No flame detected. stay cool");
            digitalWrite(buzzer, LOW);
            digitalWrite(LED, LOW);
          }
          
        }
      }
         
  
      /*if(analogRead(A0)<200){
        Serial.println("Flame detected...! take action immediately.");
        digitalWrite(buzzer, HIGH);
        digitalWrite(LED, HIGH);
        delay(200);
        }else
      {
        Serial.println("No flame detected. stay cool");
        digitalWrite(buzzer, LOW);
        digitalWrite(LED, LOW);
      }*/
      
      /*if (millis() - lastTime > 60 * 1000)
        {
            lastTime = millis();
    
            sendMessage();
        }*/
}


void sendMessage()
{

    Serial.println("------------------------------------");
    Serial.println("Send Firebase Cloud Messaging...");

    firebaseData1.fcm.setNotifyMessage("Notification", "Fire!!! "+String(latt)+","+String(lon)/*+ String(count)*/);
    firebaseData1.fcm.setDataMessage("{\"myData\":" + String(count) + "}");
//Firebase.sendMessage(firebaseData1, 0);
    //if (Firebase.broadcastMessage(firebaseData1))
    //if (Firebase.sendTopic(firebaseData1))
    if (Firebase.sendMessage(firebaseData1, 1))//send message to recipient index 0
    {

        Serial.println("PASSED");
        Serial.println(firebaseData1.fcm.getSendResult());
        Serial.println("------------------------------------");
        Serial.println();
    }
    else
    {
        Serial.println("FAILED");
        Serial.println("REASON: " + firebaseData1.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
    }

    count++;
}


/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2021 mobizt
 *
*/

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "*****"
#define WIFI_PASSWORD "99999999%%a"

/* 2. Define the API Key */
#define API_KEY "AIzaSyAbBtz7P2Lq8h_iOTu8rmHgvp3eKHccFDg"

/* 3. Define the RTDB URL */
#define DATABASE_URL "medicine-reminder-533d3-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "u1404092@student.cuet.ac.bd"
#define USER_PASSWORD "99999999"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int count = 0;
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
//LiquidCrystal lcd(D6, D7, D2, D3, D4, D5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(19, 18, 4, 2, 15, 21); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

void setup()
{

//  Serial.begin(115200);
Serial.begin(9600);
  lcd.begin(20,4);

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
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
}
void setString(String path, String valu){
FirebaseJson json;
//    json.add("value", count);
//    Serial.printf("Push json... %s\n", Firebase.pushJSON(fbdo, "/test/push", json) ? "ok" : fbdo.errorReason().c_str());
    json.set(valu);
    Firebase.updateNode(fbdo, String(path+fbdo.pushName()), json);
}
String getString(String path){
        return Firebase.getString(fbdo,path) ? String(fbdo.stringData()).c_str() : fbdo.errorReason().c_str();
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    String str= "";
    str=getString("ShortPres");
    Serial.print(str);
    lcd.clear();
//  lcd.autoscroll();
    lcd.setCursor(0,0);
    lcd.print(str);
  }
  setString("Empty/night","hello");
/*
      FirebaseJson json;
    json.add("value", count);
//    Serial.printf("Push json... %s\n", Firebase.pushJSON(fbdo, "/test/push", json) ? "ok" : fbdo.errorReason().c_str());
    json.set("value", count + 100);
//    Serial.printf("Update json... %s\n\n", Firebase.updateNode(fbdo, String("/test/push/" + fbdo.pushName()), json) ? "ok" : fbdo.errorReason().c_str());
*/
}

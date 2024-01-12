/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
*/

//This example shows how to send Firebase Cloud Messaging.

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define WIFI_SSID "CUET--Students"
#define WIFI_PASSWORD "1020304050"
#define FIREBASE_HOST "https://push-c6f5b.firebaseio.com/" 
#define FIREBASE_AUTH "qZZ2osvT5mflV86QBzgPQQYACyRuRoV6xaNtvISs"

#define FIREBASE_FCM_SERVER_KEY "AAAAwQfO-nw:APA91bFJGymr65yIHIfqziVD52D3MR91LStQ6y-MVB2v-QGbwiKRHGH9dfb37SfuCq4WbmWJt3yTygCOsYoCDGNeFRnF7aljI1QpsxvPk7kJ9TBbEexxdTcGs8hRTW07_GBmwNYRLfAE"
//#define FIREBASE_FCM_DEVICE_TOKEN_1 "eSjxq8JOrYg:APA91bHWcNX9I490NBhl_--kcKb5Zp5t5KBy0iocUbTfRQR76ZnaaKO5WjxUZk5BGoDriJ5kJAw1QjQyhZ6goBwcZUMZoiXAt9R5sg0zdyq9ziaDheDa24W1z7-McalYGpcC96nmwFOH"
//#define FIREBASE_FCM_DEVICE_TOKEN_2 "ANOTHER_RECIPIENT_DEVICE_TOKEN"
//#define FIREBASE_FCM_DEVICE_TOKEN_1 "cXn4q9o0-1A:APA91bEiUXaqN2UjEo5EgwmgFKmECGT3MEaLDqQZLzvHvuunRM8TY_igkRFxJIhUV2KOG5OjY9YHGEKZga2QkNyEHN4IhuRBZ_aP1VsSvD2bsENYLc1QCM2EaySM1uWYYjKb4YkibeFE"
#define FIREBASE_FCM_DEVICE_TOKEN_1 "fTX6MxRE_h4:APA91bEYYcAmq2WtthqyU70kEabd0cNvYs86u1XX3mcW7CNjQq1EdOdYmCzdj25zKJvYpwYVArdAhzzU0aPVIlmeeJNIHG92iixEqqQK-Ta5A82xvJjmMDHDt2qiV4WqsbABGiw6RLSo"

FirebaseData firebaseData1;

unsigned long lastTime = 0;

int count = 0;

void sendMessage();

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

    sendMessage();
}

void loop()
{
    if (millis() - lastTime > 60 * 1000)
    {
        lastTime = millis();

        sendMessage();
    }
}

void sendMessage()
{

    Serial.println("------------------------------------");
    Serial.println("Send Firebase Cloud Messaging...");

    firebaseData1.fcm.setNotifyMessage("Notification", "Amsa! " + String(count));

    firebaseData1.fcm.setDataMessage("{\"myData\":" + String(count) + "}");

    //if (Firebase.broadcastMessage(firebaseData1))
    //if (Firebase.sendTopic(firebaseData1))
    if (Firebase.sendMessage(firebaseData1, 0))//send message to recipient index 0
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

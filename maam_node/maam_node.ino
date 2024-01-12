long kotobardatapathabae = 100;
unsigned long intervaldelay = 50000;   ////8h*3600s*1000ms 
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

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
//LiquidCrystal lcd(D6, D7, D2, D3, D4, D5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(19, 18, 4, 2, 15, 21); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

void setup() {
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

String gettingdata(){
  /////////getting data from nodeMCU
  char mystr[100]={};
  char str[100]={};
  bool assign=false;
  Serial.readBytes(mystr,50); //Read the serial data and store in var
////////////Cleaning data
    for(int i=0,j=0;i<50;i++){
      if(mystr[i]=='y' && mystr[i+1]=='y'){
          assign=true;
          i+=2;
        }
      if(mystr[i]=='z'&& mystr[i+1]=='z'){
          assign=false;
          break;
        }
      if(assign==true){
        str[j]=mystr[i];
          j++;
       }
    }
    Serial.print("data: ");
//    Serial.println(mystr);
//    Serial.println();
  //////////cleaning ended
  return str;
}
String a;
char s[50];
long count=1;
long datacount=4;

void setString(String path, String valu){
FirebaseJson json;
//    json.add("value", count);
//    Serial.printf("Push json... %s\n", Firebase.pushJSON(fbdo, "/test/push", json) ? "ok" : fbdo.errorReason().c_str());
    json.set(path,valu);
    Firebase.updateNode(fbdo, String("Dispenser"+fbdo.pushName()), json);
}
String getString(String path){
        return Firebase.getString(fbdo,path) ? String(fbdo.stringData()).c_str() : fbdo.errorReason().c_str();
}

void loop() {
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    String str= "",st1="",st2="",st3="",st="";
    str=getString("Dispenser/Time");
    st1=getString("Dispenser/Prescription/night1");
    st2=getString("Dispenser/Prescription/night2");
    st3=getString("Dispenser/Prescription/night3");
    st=str+"\n"+st1+"\n"+st2+"\n"+st3;
    Serial.print(str);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str);
  lcd.setCursor(0,1);
  lcd.print(st1);
  lcd.setCursor(0,2);
  lcd.print(st2);
  lcd.setCursor(0,3);
  lcd.print(st3);
  
  }
  setString("Empty/night","hello");

    String shortpres="";
    shortpres=getString("Dispenser/Time");
    shortpres.trim();
    if(shortpres[2]!='\0'){
      String timee=shortpres.substring(shortpres.lastIndexOf('#')+1);
      for(int i=0;i<kotobardatapathabae;i++){
      Serial.write("yy");
      writeString(timee);
      Serial.write("zz");
      Serial.println();
      }
    }
    Serial.println(shortpres);
    
    String message="";
    message=gettingdata();
//    message="morning:yes,empty:1,2,3";
    message.trim();
    
    Serial.println(message);
    if(message[2]!='\0'){
    ///////////////////////////////////morning:No,empty:2,
    ///////////////////////////////////noon:No,empty:1,2,
    ///////////////////////////////////night:No,empty:1,2,

    String session="";
    String totalstr="";
    String persessionstr="";
    String pressubstr="";
    String str="";
    String emptylist="";
    int totalint=0;
    int persessionint=0;
    
    String firemorning1str="";
    String firemorning2str="";
    String firemorning3str="";
    String firenoon1str="";
    String firenoon2str="";
    String firenoon3str="";
    String firenight1str="";
    String firenight2str="";
    String firenight3str=""; 
    String morning1str="";
    String morning2str="";
    String morning3str="";
    String noon1str="";
    String noon2str="";
    String noon3str="";
    String night1str="";
    String night2str="";
    String night3str=""; 

    ///////////////////////////////////////////////////////////////////////////////morning
//    for(int k=0;k<message.length();k++){
      if(message[0]=='m'){
        firemorning1str=getString("Dispenser/Prescription/morning1");
        firemorning2str=getString("Dispenser/Prescription/morning2");
        firemorning3str=getString("Dispenser/Prescription/morning3");
        
        firenoon1str=getString("Dispenser/Prescription/noon1");
        firenoon2str=getString("Dispenser/Prescription/noon2");
        firenoon3str=getString("Dispenser/Prescription/noon3");
        
        lcd.clear();
        lcd.autoscroll();
        lcd.setCursor(0,0);
        lcd.print(firenoon1str);
        lcd.setCursor(0,1);
        lcd.print(firenoon2str);
        lcd.setCursor(0,2);
        lcd.print("noon");
        lcd.setCursor(0,3);
        lcd.print(firenoon3str);
        session="morning";
//        k=8;
        if(message[message.indexOf(':')+1]=='y'){
          session+=String(datacount/3)+" yes";
          setString("Data/data"+String(datacount-3),session);
          datacount+=1;
//          napa-2@after:total-10
          ////////////////////////morning1
          if(firemorning1str[2]!='\0'){
          totalstr=firemorning1str.substring(firemorning1str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firemorning1str.substring(firemorning1str.indexOf('-')+1,firemorning1str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firemorning1str.substring(0,firemorning1str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/morning1",str);
          }
          str="";
          }
          
          ////////////////////////morning2
          if(firemorning1str[2]!='\0'){
          totalstr=firemorning2str.substring(firemorning2str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firemorning2str.substring(firemorning2str.indexOf('-')+1,firemorning2str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firemorning2str.substring(0,firemorning2str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/morning2",str);
          }
          str="";
          }
          
          ////////////////////////morning3
          if(firemorning3str[2]!='\0'){
          totalstr=firemorning3str.substring(firemorning3str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firemorning3str.substring(firemorning3str.indexOf('-')+1,firemorning3str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firemorning3str.substring(0,firemorning3str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/morning3",str);
          }
          str="";
          }
      }
          else{
              session+=String(datacount/3)+" no";
              setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //morning:No,empty:2,
          emptylist="morning "+message.substring(message.lastIndexOf(':')+1);
          setString("Empty/morning",emptylist);
        }

        
      ///////////////////////////////////////////////////////////////////////////////noon
//    for(int k=0;k<message.length();k++){
      if(message[0]=='n'){
        
        firenoon1str=getString("Dispenser/Prescription/noon1");
        firenoon2str=getString("Dispenser/Prescription/noon2");
        firenoon3str=getString("Dispenser/Prescription/noon3");
//        lcd.clear();
//        lcd.autoscroll();
//        lcd.setCursor(0,0);
//        lcd.print(firenoon1str);
//        lcd.setCursor(0,1);
//        lcd.print(firenoon2str);
//        lcd.setCursor(0,2);
//        lcd.print("noon");
//        lcd.setCursor(0,3);
//        lcd.print(firenoon3str);
        firenight1str=getString("Dispenser/Prescription/night1");
        firenight2str=getString("Dispenser/Prescription/night2");
        firenight3str=getString("Dispenser/Prescription/night3");
        lcd.clear();
        lcd.autoscroll();
        lcd.setCursor(0,0);
        lcd.print(firenight1str);
        lcd.setCursor(0,1);
        lcd.print(firenight2str);
        lcd.setCursor(0,2);
        lcd.print("night");
        lcd.setCursor(0,3);
        lcd.print(firenight3str);
        session="noon";
//        k=8;
        if(message[message.indexOf(':')+1]=='y'){
          session+=String(datacount/3)+" yes";
          setString("Data/data"+String(datacount-3),session);
          datacount+=1;
//          napa-2@after:total-10
          ////////////////////////noon1
          if(firenoon1str[2]!='\0'){
          totalstr=firenoon1str.substring(firenoon1str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenoon1str.substring(firenoon1str.indexOf('-')+1,firenoon1str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenoon1str.substring(0,firenoon1str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/noon1",str);
          }
          str="";
          }
          
          ////////////////////////noon2
          if(firenoon2str[2]!='\0'){
          totalstr=firenoon2str.substring(firenoon2str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenoon2str.substring(firenoon2str.indexOf('-')+1,firenoon2str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenoon2str.substring(0,firenoon2str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/noon2",str);
          }
          str="";
          }
          
          ////////////////////////noon3
          if(firenoon3str[2]!='\0'){
          totalstr=firenoon3str.substring(firenoon3str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenoon3str.substring(firenoon3str.indexOf('-')+1,firenoon3str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenoon3str.substring(0,firenoon3str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/noon3",str);
          }
          str="";
          }
          }
          else{
              session+=String(datacount/3)+" no";
              setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //noon:No,empty:2,
          emptylist="noon "+message.substring(message.lastIndexOf(':')+1);
          setString("Empty/noon",emptylist);
        }
        
      ///////////////////////////////////////////////////////////////////////////////night
//    for(int k=0;k<message.length();k++){
      if(message[0]=='n' && message[1]=='i'){
        firenight1str=getString("Dispenser/Prescription/night1");
        firenight2str=getString("Dispenser/Prescription/night2");
        firenight3str=getString("Dispenser/Prescription/night3");

        firemorning1str=getString("Dispenser/Prescription/morning1");
        firemorning2str=getString("Dispenser/Prescription/morning2");
        firemorning3str=getString("Dispenser/Prescription/morning3");
        
        lcd.clear();
        lcd.autoscroll();
        lcd.setCursor(0,0);
        lcd.print(firemorning1str);
        lcd.setCursor(0,1);
        lcd.print(firemorning2str);
        lcd.setCursor(0,2);
        lcd.print("morning");
        lcd.setCursor(0,3);
        lcd.print(firemorning3str);
        session="night";
//        k=8;
        if(message[message.indexOf(':')+1]=='y'){
          session+=String(datacount/3)+" yes";
          setString("Data/data"+String(datacount-3),session);
          datacount+=1;
//          napa-2@after:total-10
          ////////////////////////night1
          if(firenight1str[2]!='\0'){
          totalstr=firenight1str.substring(firenight1str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenight1str.substring(firenight1str.indexOf('-')+1,firenight1str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenight1str.substring(0,firenight1str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/night1",str);
          }
          str="";
          }
          
          ////////////////////////night2
          if(firenight2str[2]!='\0'){
          totalstr=firenight2str.substring(firenight2str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenight2str.substring(firenight2str.indexOf('-')+1,firenight2str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenight2str.substring(0,firenight2str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/night2",str);
          }
          str="";
          }
          
          ////////////////////////night3
          if(firenight3str[2]!='\0'){
          totalstr=firenight3str.substring(firenight3str.lastIndexOf('-')+1);
          totalstr.trim();
          totalint=totalstr.toInt();
          persessionstr=firenight3str.substring(firenight3str.indexOf('-')+1,firenight3str.indexOf('-')+2);
          persessionstr.trim();
          persessionint=persessionstr.toInt();
          pressubstr=firenight3str.substring(0,firenight3str.lastIndexOf('-')+1);
          if((totalint-persessionint)>=0){
          str+=pressubstr+String(totalint-persessionint);
          setString("A/Prescription/night3",str);
          }
          str="";
          }
        }
          else{
              session+=String(datacount/3)+" no";
              setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //night:No,empty:2,
          emptylist="night "+message.substring(message.lastIndexOf(':')+1);
          setString("Empty/night",emptylist);
        }

      
      

//      setString("message",message);
//    setString("Data1/data"+String(count),"data"+String(count)+": "+message);
count=count+1;
    
  }
  
}
void writeString(String stringData) {

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);
  }

}

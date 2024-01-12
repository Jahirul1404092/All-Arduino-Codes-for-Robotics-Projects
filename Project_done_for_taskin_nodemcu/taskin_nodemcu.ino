unsigned long intervaldelay = 50000;   ////8h*3600s*1000ms 

#include "FirebaseArduino.h"
#include <ESP8266WiFi.h>
#define WIFI_SSID "RM4A"
#define WIFI_PASSWORD "cuet15@@"
//#define FIREBASE_HOST "medicine-92b8c-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "ljZxRDVVLWaiuidrAMlSNl6VU66zuokHDuBTCqjg"
#define FIREBASE_HOST "medicine-reminder-533d3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "UjzM1WIMML01O5tVfHmhiUR4VXUlEUG4bohU8DXN"
//#define WIFI_SSID "Access Denied "
//#define WIFI_PASSWORD "nitro5@504"
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(D6, D7, D2, D3, D4, D5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 


void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
  
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

void loop() {
//  String firemorning1str=Firebase.getString("Prescription/morning1");
//        String firemorning2str=Firebase.getString("Prescription/morning2");
//        String firemorning3str=Firebase.getString("Prescription/morning3");
//        lcd.clear();
//        lcd.autoscroll();
//        lcd.setCursor(0,0);
//        lcd.print(firemorning1str);
//        lcd.setCursor(0,1);
//        lcd.print(firemorning2str);
//        lcd.setCursor(0,3);
//        lcd.print(firemorning3str);
  

//    delay(100);
//    lcd.clear();
//    lcd.print("Amsa");
  
//  String firemorning1str="";
//  String totalstr="";
//  String persessionstr="";
//  String pressubstr="";
//  int totalint=0;
//  int persessionint=0;
//  firemorning1str=Firebase.getString("Prescription/morning1");
//  totalstr=firemorning1str.substring(firemorning1str.lastIndexOf('-')+1);
//  persessionstr=firemorning1str.substring(firemorning1str.indexOf('-')+1,firemorning1str.indexOf('-')+2);
//  persessionstr.trim();
//  persessionint=persessionstr.toInt();
//  totalstr.trim();
//  totalint=totalstr.toInt();
//  totalint+=2;
//  persessionint+=2;
//  pressubstr=firemorning1str.substring(0,firemorning1str.lastIndexOf('-')+1);
//  Serial.println(totalint);
//  Serial.println(persessionint);
//  Serial.println(pressubstr);
//  String str=String(totalint-persessionint);
//  Serial.println(str);
  
//    delay(100);
//    lcd.clear();
//    lcd.print("Amsa");
//    lcd.setCursor(2,1);
//    lcd.print("400"); 
    
    String message="";
    message=gettingdata();
//    message="morning:yes,empty:1,2,3";
    message.trim();
    
//    delay(100);
//    if(message[2]!='\0'){
//    lcd.clear();
//    lcd.print(message);}
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
        firemorning1str=Firebase.getString("Prescription/morning1");
        firemorning2str=Firebase.getString("Prescription/morning2");
        firemorning3str=Firebase.getString("Prescription/morning3");
        
        firenoon1str=Firebase.getString("Prescription/noon1");
        firenoon2str=Firebase.getString("Prescription/noon2");
        firenoon3str=Firebase.getString("Prescription/noon3");
        
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
          Firebase.setString("Data/data"+String(datacount-3),session);
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
          Firebase.setString("Prescription/morning1",str);
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
          Firebase.setString("Prescription/morning2",str);
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
          Firebase.setString("Prescription/morning3",str);
          }
          str="";
          }
      }
          else{
              session+=String(datacount/3)+" no";
              Firebase.setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //morning:No,empty:2,
          emptylist="morning "+message.substring(message.lastIndexOf(':')+1);
          Firebase.setString("Empty/morning",emptylist);
        }

        
      ///////////////////////////////////////////////////////////////////////////////noon
//    for(int k=0;k<message.length();k++){
      if(message[0]=='n'){
        
        firenoon1str=Firebase.getString("Prescription/noon1");
        firenoon2str=Firebase.getString("Prescription/noon2");
        firenoon3str=Firebase.getString("Prescription/noon3");
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
        firenight1str=Firebase.getString("Prescription/night1");
        firenight2str=Firebase.getString("Prescription/night2");
        firenight3str=Firebase.getString("Prescription/night3");
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
          Firebase.setString("Data/data"+String(datacount-3),session);
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
          Firebase.setString("Prescription/noon1",str);
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
          Firebase.setString("Prescription/noon2",str);
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
          Firebase.setString("Prescription/noon3",str);
          }
          str="";
          }
          }
          else{
              session+=String(datacount/3)+" no";
              Firebase.setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //noon:No,empty:2,
          emptylist="noon "+message.substring(message.lastIndexOf(':')+1);
          Firebase.setString("Empty/noon",emptylist);
        }
        
      ///////////////////////////////////////////////////////////////////////////////night
//    for(int k=0;k<message.length();k++){
      if(message[0]=='n' && message[1]=='i'){
        firenight1str=Firebase.getString("Prescription/night1");
        firenight2str=Firebase.getString("Prescription/night2");
        firenight3str=Firebase.getString("Prescription/night3");

        firemorning1str=Firebase.getString("Prescription/morning1");
        firemorning2str=Firebase.getString("Prescription/morning2");
        firemorning3str=Firebase.getString("Prescription/morning3");
        
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
          Firebase.setString("Data/data"+String(datacount-3),session);
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
          Firebase.setString("Prescription/night1",str);
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
          Firebase.setString("Prescription/night2",str);
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
          Firebase.setString("Prescription/night3",str);
          }
          str="";
          }
        }
          else{
              session+=String(datacount/3)+" no";
              Firebase.setString("Data/data"+String(datacount-3),session);
              datacount+=1;
            }
                //night:No,empty:2,
          emptylist="night "+message.substring(message.lastIndexOf(':')+1);
          Firebase.setString("Empty/night",emptylist);
        }

      
      

//      Firebase.setString("message",message);
//    Firebase.setString("Data1/data"+String(count),"data"+String(count)+": "+message);
count=count+1;
    
  }
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
  }

}

void writeString(String stringData) {

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);
  }

}






























/*
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "waterquality-44fa9-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PVqQbCVmgCm50CHTSyFbGaWDBjRIXvUTqFRYUOKq"
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD ""
//#define WIFI_SSID "Access Denied "
//#define WIFI_PASSWORD "nitro5@504"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

String getdata(){
  /////////getting data from nodeMCU
  char mystr[1000]={};
  char str[1000]={};
  bool assign=false;
  Serial.readBytes(mystr,300); //Read the serial data and store in var
////////////Cleaning data
    for(int i=0,j=0;i<50;i++){
      if(mystr[i]=='A' && mystr[i+1]=='A'){
          assign=true;
          i+=2;
        }
      if(mystr[i]=='B'&& mystr[i+1]=='B'){
          assign=false;
          break;
        }
      if(assign==true){
        str[j]=mystr[i];
          j++;
       }
    }
//    Serial.print("data: ");
//    Serial.println(mystr);
//    Serial.println();
  //////////cleaning ended
  return str;
}


String a;
char s[500];

int i=0;
void loop() {
  i++;
  String dataa="";
//  String ph="",tds="",tur="",temp="";
char ph[10]={};
char tds[10]={};
char tur[10]={};
char temp[10]={};
  // set string value
  dataa=getdata();
// Serial.println(dataa);
// Serial.println();
 delay(1000);
// for(int i=0;i<dataa.length();i++){
//  Serial.println(dataa[i]);
//  }
if(dataa[5]!='\0'){
int loc=0;
for(int i=loc,j=0;i<dataa.length();i++,j++){
  if(dataa[i]==','){
    Serial.println("temp");
    Serial.println(temp);
    loc=i+1;
  break;
  }else{
//    Serial.print(dataa[i]);
    temp[j]=dataa[i];
//    temp+=dataa[i];
    }
  }
for(int i=loc,j=0;i<dataa.length();i++,j++){
  if(dataa[i]==','){
    Serial.println("tur");
    Serial.println(tur);
    loc=i+1;
  break;
  }else{
//    Serial.print(dataa[i]);
    tur[j]=dataa[i];
//    tur+=dataa[i];
    }
  }
for(int i=loc,j=0;i<dataa.length();i++,j++){
  if(dataa[i]==','){
    Serial.println("tds");
    Serial.println(tds);
    loc=i+1;
  break;
  }else{
//    Serial.print(dataa[i]);
    tds[j]=dataa[i];
//    tds+=dataa[i];
    }
  }
 for(int i=loc,j=0;i<dataa.length();i++,j++){
  if(dataa[i]==','){
    
    loc=i+1;
  break;
  }else{
//    Serial.print(dataa[i]);
    ph[j]=dataa[i];
//    ph+=dataa[i];
    }
  }
  Serial.println("ph");
  Serial.println(ph);
  
    Firebase.setString("pH/"+String(i), ph);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }delay(100);
  
  Firebase.setString("TDS/"+String(i),tds);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }delay(100);
  
  Firebase.setString("Temperature/"+String(i), temp);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }delay(100);
  
  Firebase.setString("Turbidity/"+String(i), tur);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(100);
    }
  
  
  delay(1000);
  
}
*/

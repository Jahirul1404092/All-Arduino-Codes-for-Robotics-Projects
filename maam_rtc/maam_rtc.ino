#include <Wire.h>
#include <ds3231.h>
 
struct ts t; 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  t.hour=18; 
  t.min=41;
  t.sec=0;
  t.mday=12;
  t.mon=1;
  t.year=2022;
 
  DS3231_set(t); 
}
String gettingdata(){
  /////////getting data from nodeMCU
  char mystr[1050]={};
  char str[1050]={};
  bool assign=false;
  Serial.readBytes(mystr,200); //Read the serial data and store in var
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
//    Serial.println(str);
//    Serial.println();
  //////////cleaning ended
  return str;
}
 String datee="";
void loop() {
  
  DS3231_get(&t);
  Serial.print("Date : ");
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);
  delay(1000);
  
  String message="";
    message=gettingdata();
    message.trim();
    Serial.println(message);
}

#define sensmorning1 2
#define sensmorning2 3
#define sensmorning3 4
#define morningled 5
#define sensnoon1 6
#define sensnoon2 7
#define sensnoon3 8
#define noonled 9
#define sensnight1 10
#define sensnight2 11
#define sensnight3 12
#define nightled 13
#define buzzer A1
#define emptymedicineled A0
bool morningflag=false;
bool noonflag=false;
bool nightflag=false;

//unsigned long intervaldelay = 28800000;   ////8h*3600s*1000ms 
unsigned long intervaldelay = 5000;   ////8h*3600s*1000ms 
long dooropendelay = 60;   ///10min*60s
long doorclosdelay = 10000;   ///10min*60s
long kotobardatapathabae = 100;
unsigned long freqllis = 0;
long timediffinmillis=0;
String rcvmessage="";
String sendmessage="";
String emptylist="";

#include <SoftwareSerial.h>
SoftwareSerial mySerial(A4, A5); //SIM900 Tx & Rx is connected to Arduino #7 & #8
//rtc
#include <Wire.h>
#include <ds3231.h>
struct ts t; 

void setup() {
  Serial.begin (9600);
  mySerial.begin(9600);
  pinMode(sensmorning1,INPUT);
  pinMode(sensmorning2,INPUT);
  pinMode(sensmorning3,INPUT);
  pinMode(sensnoon1,INPUT);
  pinMode(sensnoon2,INPUT);
  pinMode(sensnoon3,INPUT);
  pinMode(sensnight1,INPUT);
  pinMode(sensnight2,INPUT);
  pinMode(sensnight3,INPUT);
  
  pinMode(buzzer,OUTPUT);
  pinMode(emptymedicineled, OUTPUT);
  pinMode(morningled,OUTPUT);
  pinMode(noonled,OUTPUT);
  pinMode(nightled,OUTPUT);

  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  t.hour=17; 
  t.min=59;
  t.sec=0;
  t.mday=13;
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
//    Serial.print("data: ");
//    Serial.println(str);
//    Serial.println();
  //////////cleaning ended
  return str;
}

//////////writing to NodeMcu
void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}// end writeString

int h=100,m=100;
void loop() {
//  digitalWrite(morningled,HIGH);
//  digitalWrite(noonled,HIGH);
//  digitalWrite(nightled,HIGH);

//  if(digitalRead(sensmorning1)==LOW){Serial.println("m1 ache");}else{Serial.println("m1 nai");}
//  if(digitalRead(sensmorning2)==LOW){Serial.println("m2 ache");}else{Serial.println("m2 nai");}
//  if(digitalRead(sensmorning3)==LOW){Serial.println("m3 ache");}else{Serial.println("m3 nai");}
//  if(digitalRead(sensnoon1)==LOW){Serial.println("n1 ache");}else{Serial.println("n1 nai");}
//  if(digitalRead(sensnoon2)==LOW){Serial.println("n2 ache");}else{Serial.println("n2 nai");}
//  if(digitalRead(sensnoon3)==LOW){Serial.println("n3 ache");}else{Serial.println("n3 nai");}
//  if(digitalRead(sensnight1)==LOW){Serial.println("nt1 ache");}else{Serial.println("nt1 nai");}
//  if(digitalRead(sensnight2)==LOW){Serial.println("nt2 ache");}else{Serial.println("nt2 nai");}
//  if(digitalRead(sensnight3)==LOW){Serial.println("nt3 ache");}else{Serial.println("nt3 nai");}
//  delay(100);

  DS3231_get(&t);
  Serial.print(t.hour);
  Serial.print(":");
  Serial.println(t.min);
  Serial.print(":");
  Serial.println(t.sec);
  
  String timee="A",hr="",mn="";
  
  timee=gettingdata();
//  Serial.print(timee);

  if(timee[1]!='\0'){
  hr=timee.substring(0,timee.indexOf(':'));
  mn=timee.substring(timee.indexOf(':')+1);
  h =hr.toInt();
  m=mn.toInt();
  long t1=(t.hour*60*60)+(t.min*60);
  long t2=(h*60*60)+(m*60);
  timediffinmillis=(t1-t2)*1000;
  timediffinmillis=abs(timediffinmillis);
  Serial.print("h: ");
    Serial.println(h);
    Serial.print("m: ");
    Serial.println(m);
      
  }
  
  
  Serial.println(timediffinmillis);
  Serial.print("fre: ");
  Serial.println(freqllis);
  Serial.print("fredif: ");
  Serial.println(millis() - freqllis);
  if((timediffinmillis!=0 && timediffinmillis<=110000) && (millis() - freqllis > 60000 || freqllis==0 )){
    freqllis = millis();
//    Serial.print("h: ");
//    Serial.println(h);
  

  morningflag=false;
  noonflag=false;
  nightflag=false;

  if(h>=5 && h<12){
  Serial.println("morning-------");
  //////////////////////////////////////////////////////////////////////////////////////////////////////////morning //6ta
  digitalWrite(morningled,HIGH);
  digitalWrite(buzzer,HIGH);
  Serial.println("alerm");
  for(int i=0;i<dooropendelay;i++){
    if(digitalRead(sensmorning1)==HIGH && digitalRead(sensmorning2)==HIGH && digitalRead(sensmorning3)==HIGH){
      //////morning door opened
        digitalWrite(morningled,LOW);
        digitalWrite(buzzer,LOW);
        ////send to node that morning oshudh khaiche
        Serial.println("opened");
        sendmessage+="morning:yes,";
        morningflag=true;
        break;
      }
      delay(1000);
  }
  if(morningflag==false){
    ////send to node that morning oshudh khaynai
    Serial.println("khaynai");
    sendmessage+="morning:no,";
    digitalWrite(morningled,LOW);
    digitalWrite(buzzer,LOW);
  }
  
  delay(doorclosdelay);
  //////////////////////checking for closing door and checking which containainer has medicine or not
  for(int i=0;i<60;i++){
    if(digitalRead(sensmorning1)==LOW || digitalRead(sensmorning2)==LOW || digitalRead(sensmorning3)==LOW){
      Serial.println("closed");
      if(digitalRead(sensmorning1)==HIGH){
        emptylist+="1,";
        }
      if(digitalRead(sensmorning2)==HIGH){
        emptylist+="2,";
        }
      if(digitalRead(sensmorning3)==HIGH){
        emptylist+="3";
        }
        break;
      }
      Serial.println(emptylist);
      
      delay(1000);
    }
    if(emptylist[0]!='\0'){
      for(int i=0;i<20;i++){
        digitalWrite(buzzer,HIGH);
        digitalWrite(emptymedicineled,HIGH);
        delay(400);
        digitalWrite(buzzer,LOW);
        digitalWrite(emptymedicineled,LOW);
        if(i%3==0){
          delay(1000);}else{delay(200);}
        }
      }
    sendmessage+="empty:"+emptylist;
//  Serial.println(sendmessage);
  for(int i=0;i<kotobardatapathabae;i++){
  Serial.write("yy");
  writeString(sendmessage);
  Serial.write("zz");
  Serial.println();
  }
  sendmessage="";
  emptylist="";

  
//  delay(intervaldelay);
  }

if(h>=12 && h<18){
//////////////////////////////////////////////////////////////////////////////////////////////////////////noon //6ta
Serial.println("noon---------");
    digitalWrite(noonled,HIGH);
    digitalWrite(buzzer,HIGH);
  Serial.println("alarm");
          for(int i=0;i<dooropendelay;i++){
        if(digitalRead(sensnoon1)==HIGH && digitalRead(sensnoon2)==HIGH && digitalRead(sensnoon3)==HIGH){
        //////noon door opened
        digitalWrite(noonled,LOW);
        digitalWrite(buzzer,LOW);
        ////send to node that noon oshudh khaiche
        Serial.println("opened");
        sendmessage+="noon:yes,";
        noonflag=true;
        break;
        }
        delay(100);
        }
        if(noonflag==false){
        ////send to node that noon oshudh khaynai
        Serial.println("khaynai");
        sendmessage+="noon:no,";
        digitalWrite(noonled,LOW);
        digitalWrite(buzzer,LOW);
        }

        delay(doorclosdelay);
        //////////////////////checking for closing door and checking which containainer has medicine or not
        for(int i=0;i<60;i++){
        if(digitalRead(sensnoon1)==LOW || digitalRead(sensnoon2)==LOW || digitalRead(sensnoon3)==LOW){
        Serial.println("closed");
        if(digitalRead(sensnoon1)==HIGH){
        emptylist+="1,";
        }
        if(digitalRead(sensnoon2)==HIGH){
        emptylist+="2,";
        }
        if(digitalRead(sensnoon3)==HIGH){
        emptylist+="3";
        }
        break;
        }
        Serial.println(emptylist);

        delay(1000);
        }
        if(emptylist[0]!='\0'){
        for(int i=0;i<20;i++){
        digitalWrite(buzzer,HIGH);
        digitalWrite(emptymedicineled,HIGH);
        delay(400);
        digitalWrite(buzzer,LOW);
        digitalWrite(emptymedicineled,LOW);
        if(i%3==0){
        delay(1000);}else{delay(200);}
        }
        }
        sendmessage+="empty:"+emptylist;
//  Serial.println(sendmessage);
        for(int i=0;i<kotobardatapathabae;i++){
        Serial.write("yy");
        writeString(sendmessage);
        Serial.write("zz");
        Serial.println();
        }
        sendmessage="";
        emptylist="";


//        delay(intervaldelay);
}

if((h>=18 && h<=23) || (h>=0 && h<5)){
Serial.println("night----------------");
//////////////////////////////////////////////////////////////////////////////////////////////////////////night //6ta
    digitalWrite(nightled,HIGH);
    digitalWrite(buzzer,HIGH);
  Serial.println("alerm");
  delay(10000);
      for(int i=0;i<dooropendelay;i++){
        if(digitalRead(sensnight1)==HIGH && (digitalRead(sensnight2)==HIGH && digitalRead(sensnight3)==HIGH)){
        //////night door opened
        digitalWrite(nightled,LOW);
        digitalWrite(buzzer,LOW);
        ////send to node that night oshudh khaiche
        Serial.println("opened");
        sendmessage+="night:yes,";
        nightflag=true;
        break;
        }
        delay(1000);
        }
        if(nightflag==false){
        ////send to node that night oshudh khaynai
        Serial.println("khaynai");
        sendmessage+="night:no,";
        digitalWrite(nightled,LOW);
        digitalWrite(buzzer,LOW);
        }

        delay(doorclosdelay);
        //////////////////////checking for closing door and checking which containainer has medicine or not
        for(int i=0;i<60;i++){
        if(digitalRead(sensnight1)==LOW || digitalRead(sensnight2)==LOW || digitalRead(sensnight3)==LOW){
        Serial.println("closed");
        if(digitalRead(sensnight1)==HIGH){
        emptylist+="1,";
        }
        if(digitalRead(sensnight2)==HIGH){
        emptylist+="2,";
        }
        if(digitalRead(sensnight3)==HIGH){
        emptylist+="3";
        }
        break;
        }
        Serial.println(emptylist);

        delay(1000);
        }
        if(emptylist[0]!='\0'){
        for(int i=0;i<20;i++){
        digitalWrite(buzzer,HIGH);
        digitalWrite(emptymedicineled,HIGH);
        delay(400);
        digitalWrite(buzzer,LOW);
        digitalWrite(emptymedicineled,LOW);
        if(i%3==0){
        delay(1000);}else{delay(200);}
        }
        }
        sendmessage+="empty:"+emptylist;
//  Serial.println(sendmessage);
        for(int i=0;i<kotobardatapathabae;i++){
        Serial.write("yy");
        writeString(sendmessage);
        Serial.write("zz");
        Serial.println();
        }
        sendmessage="";
        emptylist="";


//        delay(intervaldelay);
 }
}

}

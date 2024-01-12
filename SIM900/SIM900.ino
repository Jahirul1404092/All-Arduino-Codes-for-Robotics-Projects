#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // configure software serial port 
int REDLed= 2;
int GREENLed= 3;
int BLUELed= 4;
int cnt;
void setup() {     
  
  pinMode(REDLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  SIM900.begin(19200);
  Serial.begin(19200); 
  Serial.print("power up" );
  delay(3000); 

}


 
void loop()
{

  Serial.println("SubmitHttpRequest - started" );
  SubmitHttpRequest();
  Serial.println("SubmitHttpRequest - finished" );
  delay(10000);

}

void SubmitHttpRequest()
{
 
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"gpinternet\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
  
  SIM900.println("AT+SAPBR=0,1");//setting the SAPBR
  delay(2000); 
  ShowSerialData();
  
  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
  delay(3000);
 
  SIM900.println("AT+HTTPTERM"); //init the HTTP request
  delay(2000); 
  ShowSerialData();
  
  SIM900.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();
 
  SIM900.println("AT+HTTPPARA=\"URL\",\"hotelmiskha.com/t.php\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(1000);
  changeLed();
  
  //ShowSerialData();
//  while(SIM900.available()!=0){
//    int val=int(SIM900.read());
//   // Serial.write(char (SIM900.read()));
//  Serial.println(val);
//}
  SIM900.println("");
  delay(100);
}
 
void changeLed()
{
 String content = "";
// String RedState = content.substring();
 while(SIM900.available()!=0)
 {  
    //Serial.write(SIM900.read());
    content = content + String(char (SIM900.read()));
 }
    
    //Serial.println(content);
    digitalWrite(11,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    for(int i=0;content[i];i++){
        Serial.println(content[i]);
       if(content[i]=='Z'){
       if(content[i+1]=='Z'){
       for(int j=i+2;(content[j]>='1' && content[j]<='9');j++){
       if(content[j]=='1')
       {
        digitalWrite(9,HIGH);
        }

        if(content[j]=='2')
       {
        digitalWrite(10,HIGH);
        }


      if(content[j]=='3')
       {
        digitalWrite(11,HIGH);
        }
       }
       }
       }
       }
 /* if(content){
  Serial.println("Loop");
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  }*/
 content = "";
}

 
void ShowSerialData()
{
  while(SIM900.available()!=0){
    Serial.write(char (SIM900.read()));
    
}
}

int buzzer = 13;
int light = 19;
int sensor = 4;
int relay = 12;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop() {

//    Serial.println(analogRead(A3));
//    delay(500);
    if(digitalRead(sensor)==HIGH){
      int val=analogRead(A3);
      if(val<=15){
//        Serial.println(val);
        digitalWrite(buzzer,HIGH);
        for(int l=0;l<=18;l++){
          digitalWrite(relay,HIGH);
          delay(800);
          digitalWrite(relay,LOW);
          delay(500);
        }
        digitalWrite(buzzer,LOW);
        delay(1000);
        

//        digitalWrite(buzzer,HIGH);
//        digitalWrite(relay,HIGH);
//        digitalWrite(light,HIGH);
//        delay(2000);
//        digitalWrite(buzzer,LOW);
//        digitalWrite(relay,LOW);
//        digitalWrite(light,LOW);
//        delay(500);
//    
//        digitalWrite(buzzer,HIGH);
//        digitalWrite(relay,HIGH);
//        digitalWrite(light,HIGH);
//        delay(1000);
//        digitalWrite(buzzer,LOW);
//        digitalWrite(relay,LOW);
//        digitalWrite(light,LOW);
//        delay(500);
//        digitalWrite(buzzer,HIGH);
//        digitalWrite(relay,HIGH);
//        digitalWrite(light,HIGH);
//        delay(2000);
//        digitalWrite(buzzer,LOW);
//        digitalWrite(relay,LOW);
//        digitalWrite(light,LOW);
//        delay(500);
        }
      
      }
}

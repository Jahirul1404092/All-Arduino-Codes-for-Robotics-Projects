                                                                                                                                                                                                                                                                                                                                                                                                                                              // Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin1 = A0; 
int servoPin2 = A1;
int servoPin3= A2;  
int servoPin4= A3;  
int i;
// Create a servo object 
Servo Servo1; 
Servo Servo2;
Servo Servo3;
Servo Servo4;  
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1); 
   Servo2.attach(servoPin2); 
   Servo3.attach(servoPin3); 
   Servo3.attach(servoPin4); 
}
void loop(){ 
   for(i=68;i<=118;i+=1){
   Servo1.write(i); 
   delay(50);
   Serial.println("servo1");
    }  
   for(i=118;i>=68;i-=1){
   Servo1.write(i); 
   delay(50);
   Serial.println("servo1");
    } 

delay(100);

       for(i=68;i<=118;i+=1){
   Servo2.write(i); 
   delay(50);
   Serial.println("servo2");
    }  
   for(i=118;i>=68;i-=1){
   Servo2.write(i); 
   delay(50);
   Serial.println("servo2");
    } 


delay(100);

         for(i=68;i<=118;i+=1){
   Servo3.write(i); 
   delay(50);
   Serial.println("servo3");
    }  
   for(i=118;i>=68;i-=1){
   Servo3.write(i); 
   delay(50);
   Serial.println("servo3");
    } 



delay(100);
             for(i=68;i<=118;i+=1){
   Servo4.write(i); 
   delay(50);
   Serial.println("servo4");
    }  
   for(i=118;i>=68;i-=1){
   Servo4.write(i); 
   delay(50);
   Serial.println("servo4");
    }
}

                                                                                                                                                                                                                                                                                                                                                                                                                                              // Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = A2; 
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
  
   for(int i=0;i<=180;i+=3){
   Servo1.write(i); 
   delay(50);
    }  
   for(int i=180;i>=0;i-=3){
   Servo1.write(i); 
   delay(50);
    } 
    delay(5000);
}

int piezoPin = 11;
int i=0;
void setup() {
//digitalWrite(11,LOW);

}//close setup

void loop() {

  /*Tone needs 2 arguments, but can take three
    1) Pin#
    2) Frequency - this is in hertz (cycles per second) which determines the pitch of the noise made
    3) Duration - how long teh tone plays
  */
  
//  digitalWrite(11,HIGH);
  tone(piezoPin, i, 3000);
  i++;
  Serial.println(i);

  //tone(piezoPin, 1000, 500);
  //delay(1000);

}

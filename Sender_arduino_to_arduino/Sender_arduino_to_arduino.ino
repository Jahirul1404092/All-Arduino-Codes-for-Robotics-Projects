char mystr[1000] = "Hellogvekfffffffffffffffffffffffff333"; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.write(mystr); //Write the serial data
  delay(1000);
}

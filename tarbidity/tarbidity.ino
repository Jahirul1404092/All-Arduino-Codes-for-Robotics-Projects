int y;
float a;
float b;
float NTU;
void setup() {
  Serial.begin(9600); //Baud rate: 9600
}
void loop() {
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.println(voltage); // print out the value you read:
  //////finding NTU from NTU-voltage curve eqn: NTU= -1120.4v2+5742.3v-4352.9
  b=5742.3*voltage;
  voltage=voltage*voltage;
  a=1120.4*voltage;
  b=b-4352.9;
  NTU=b-a;
  Serial.println(NTU);
  delay(500);
}

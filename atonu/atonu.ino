#define pir 3
#define vibration 4
#define water 5
#define MQ3pin A5
#define ldr A2
#define ThermistorPin A4

float alcoholvalue = 0.0;
//////////////////////////////////////////////////////////mouse
#include <Mouse.h>

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 8;   // switch to turn on and off mouse control
const int mouseButton = 9; // input pin for the mouse pushButton
const int xAxis = A0;      // joystick X axis
const int yAxis = A1;      // joystick Y axis
const int ledPin = 36;     // Mouse control LED

// parameters for reading the joystick:
int range = 12;            // output range of X or Y movement
int responseDelay = 5;     // response delay of the mouse, in ms
int threshold = range / 4; // resting threshold
int center = range / 2;    // resting position value

bool mouseIsActive = false; // whether or not to control the mouse
int lastSwitchState = LOW;  // previous switch state

//////////////////////////////////////////////////////////soundsensor
int soundsensor = A6;
//////////////////////////////////////////////////////////moisture
int moisturesensor = A7;
int sensorValue;
int limit = 300;
/////////////////////////////////////////////////////////sonar
int trigPin = 6; // Trigger
int echoPin = 7; // Echo  kaje lagbe
long duration, cm, inches;

///////////////////////////////////////////////////////////////Key4*4
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {

    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

////////////////////////////////////////////////////////////////////////////////////temp
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 9

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature tempsensor(&oneWire);

float Celcius = 0;
float Fahrenheit = 0;
/////////////////////////////////////////////////////////////////////display
#include <LiquidCrystal.h>                 // includes the LiquidCrystal Library
LiquidCrystal lcd(30, 31, 32, 33, 34, 35); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

void setup()
{
  Serial.begin(9600);
  tempsensor.begin();
  pinMode(pir, INPUT);
  pinMode(vibration, INPUT);
  pinMode(water, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(moisturesensor, INPUT);
  pinMode(soundsensor, INPUT);
  pinMode(ldr, INPUT);

  pinMode(switchPin, INPUT); // the switch pin
  Mouse.begin();
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
}

void getkey(String password)
{
  int T = 2000;
  delay(1);
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    int match = 0;
    int j = 0;
    char key_pass[20] = {};
    int sum = 0;
    key_pass[0] = key;
    int pass_input_time = 3000;
    if (key_pass[j] == password[j])
    {
      sum += 1;
      j++;
    }
    int i = pass_input_time;
    int len = password.length();

    while (i--)
    {

      for (int i = 0; i < pass_input_time; i++)
      {
        Serial.print(key_pass);
        Serial.println();
        key_pass[j] = keypad.getKey();
        if (key_pass[j] != NO_KEY)
        {
          j++;
          break;
        }
        Serial.print(key_pass);
      }
    }
  }
}

void gettemp()
{
  int Vo;
  float R1 = 1000;
  float logR2, R2, T, C;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  T = (T * 9.0) / 5.0 + 32.0;
  T = T - 100;
  C = (T - 32) / 1.8;

  Serial.print("Temperature: ");
  Serial.print(C);
  Serial.println(" C");
}

void getpir()
{
  if (digitalRead(pir) == HIGH)
  {
    Serial.println("PIR HIGH");

    lcd.clear();
    lcd.print("PIR HIGH");
  }
  else
  {
    Serial.println("PIR LOW");
    lcd.clear();
    lcd.print("PIR LOW");
  }
}
void getvibration()
{
  if (digitalRead(vibration) == HIGH)
  {
    Serial.println("vibration HIGH");
    lcd.clear();
    lcd.print("Vibration HIGH");
  }
  else
  {
    Serial.println("vibration LOW");
    
    lcd.clear();
    lcd.print("vibration LOW");
  }
}
void getwater()
{
  if (digitalRead(water) == HIGH)
  {
    Serial.println("water HIGH");

    lcd.clear();
    lcd.print("Water HIGH");
  }
  else
  {
    Serial.println("water LOW");

    lcd.clear();
    lcd.print("Water LOW");
  }
}

void getalcohol()
{
  alcoholvalue = analogRead(MQ3pin);
  Serial.print("Sensor Value: ");
  Serial.println(alcoholvalue);

  lcd.clear();
  lcd.print("alcohol");
  lcd.print(alcoholvalue);
}

void getsonar()
{
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 70; // Divide by 74 or multiply by 0.0135

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(250);
  lcd.clear();
  lcd.print("sonar ");
  lcd.print(cm);
}
void getmoisture()
{
  sensorValue = analogRead(moisturesensor);
  sensorValue -= 1023;
  if (sensorValue < 0)
  {
    sensorValue = -1 * sensorValue;
  }
  Serial.println("Analog Value : ");
  Serial.println(sensorValue);
  lcd.clear();
  lcd.print("Moisture ");
  lcd.print(sensorValue);
}
void getsound()
{
  int val;
  val = analogRead(soundsensor); //connect mic sensor to Analog 0
  Serial.print("Sound=");
  Serial.println(val, DEC); //print the sound value to serial
  lcd.clear();
  lcd.print("Sound ");
  lcd.print(val);
}
void getlight()
{
  int val;
  val = analogRead(ldr); //connect mic sensor to Analog 0
  Serial.print("Light=");
  Serial.println(val); //print the sound value to serial

  lcd.clear();
  lcd.print("Light ");
  lcd.print(val);
}

void getmouse()
{
  // read the switch:
  int switchState = digitalRead(switchPin);
  switchState = HIGH;
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState)
  {
    if (switchState == HIGH)
    {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read and scale the two axes:
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive)
  {
    Mouse.move(xReading, yReading, 0);
    Serial.println(xReading);
    Serial.println(yReading);

    lcd.clear();
    lcd.print("x: ");
    lcd.print(xReading);
    lcd.print("y: ");
    lcd.print(yReading);
  }

  // read the mouse button and click or not click:
  // if the mouse button is pressed:
  if (digitalRead(mouseButton) == HIGH)
  {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT))
    {
      Mouse.press(MOUSE_LEFT);
      Serial.println("Button Pressed");
    }
  }
  // else the mouse button is not pressed:
  else
  {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT))
    {
      Mouse.release(MOUSE_LEFT);
      Serial.println("Button Pressed");
    }
  }

  delay(responseDelay);
}
int readAxis(int thisAxis)
{
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold)
  {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}
void getdisplay()
{
  lcd.clear();
  lcd.print("Display");
}

void loop()
{
  int T=1000;
  char key=' ';
  while(T--){
    key = keypad.getKey();
    }
  if(key=='1'){
    gettemp();
  }else if(key=='2'){
    getpir();
  }else if(key=='3'){
    getdisplay();
  }else if(key=='4'){
    getmouse();
  }else if(key=='5'){
    getlight();
  }else if(key=='6'){
    getmoisture();
  }else if(key=='7'){
    getsound();
  }else if(key=='8'){
    getsonar();
  }else if(key=='9'){
    getalcohol();
  }else if(key=='0'){
    gettemp();
  }else if(key=='1'){
    getvibration();
  }
  delay(5000);

  
  // gettemp();
  //  getpir();
  //   getdisplay();
  // getmouse();
  // getlight();
  // getmoisture();
  // getsound();
  // getsonar();
  // getalcohol();
  // getvibration();
}




/*#define pir 3
#define vibration 4
#define water 5
#define MQ3pin A5
#define ldr A2
float alcoholvalue=0.0;
//////////////////////////////////////////////////////////mouse
#include <Mouse.h>

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 8;      // switch to turn on and off mouse control
const int mouseButton = 9;    // input pin for the mouse pushButton
const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
const int ledPin = 36;         // Mouse control LED

// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value

bool mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

//////////////////////////////////////////////////////////soundsensor
int soundsensor = A6; 
//////////////////////////////////////////////////////////moisture
int moisturesensor = A7; 
int sensorValue;  
int limit = 300;
/////////////////////////////////////////////////////////sonar
int trigPin = 6;    // Trigger
int echoPin = 7;    // Echo  kaje lagbe
long duration, cm, inches;


///////////////////////////////////////////////////////////////Key4*4
#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

////////////////////////////////////////////////////////////////////////////////////temp
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempsensor(&oneWire);

 float Celcius=0;
 float Fahrenheit=0;
/////////////////////////////////////////////////////////////////////display
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(30, 31, 32, 33, 34, 35); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
 

void setup(){
  Serial.begin(9600);
  tempsensor.begin();
  pinMode(pir,INPUT);
  pinMode(vibration,INPUT);
  pinMode(water,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(moisturesensor,INPUT);
  pinMode(soundsensor,INPUT);
  pinMode(ldr,INPUT);
  pinMode(switchPin, INPUT);       // the switch pin
  Mouse.begin();
  pinMode(ledPin, OUTPUT);
lcd.begin(16,2);
}


void getkey(String password){
   int T=2000;
    delay(1);
   char key = keypad.getKey(); 
  if (key != NO_KEY){
    int match=0;
    int j=0;
    char key_pass[20]={};
    int sum=0;
    key_pass[0]=key;
    int pass_input_time=3000;
    if(key_pass[j]==password[j]){sum+=1;j++;}
    int i=pass_input_time;
    int len=password.length();
    
    while(i--){
        
       for(int i=0;i<pass_input_time;i++){
        Serial.print(key_pass);
              Serial.println();
              key_pass[j]=keypad.getKey();
              if(key_pass[j]!=NO_KEY){
                  j++;
                  break;}
              Serial.print(key_pass);}
              }       
  }
}

void gettemp(){
//  tempsensor.requestTemperatures(); 
//  Celcius=sensors.getTempCByIndex(0);
//  Serial.print("temp : ");
//  Serial.println(Celcius);
}

void getpir(){
  if(digitalRead(pir)==HIGH){
    Serial.println("PIR HIGH");}
    else{
      Serial.println("PIR LOW");}}
void getvibration(){
  if(digitalRead(vibration)==HIGH){
    Serial.println("vibration HIGH");}
    else{
      Serial.println("vibration LOW");}}
void getwater(){
  if(digitalRead(water)==HIGH){
    Serial.println("water HIGH");}
    else{
      Serial.println("water LOW");}}
      
void getalcohol(){
  sensorValue = analogRead(MQ3pin);
  Serial.print("Sensor Value: ");
  Serial.print(alcoholvalue);}
  
void getsonar(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 70;   // Divide by 74 or multiply by 0.0135

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
void getmoisture(){
  sensorValue = analogRead(moisturesensor); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 delay(1000); 
 }
 void getsound(){
  int val;
  val=analogRead(soundsensor);   //connect mic sensor to Analog 0
  Serial.print("Sound=");
  Serial.println(val,DEC);//print the sound value to serial        
}
void getlight(){
  int val;
  val=analogRead(ldr);   //connect mic sensor to Analog 0
  Serial.print("Light=");
  Serial.println(val);//print the sound value to serial        
}

void getmouse() {
  // read the switch:
  int switchState = digitalRead(switchPin);
  switchState=HIGH;
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read and scale the two axes:
  int xReading = readAxis(A0);
  int yReading = readAxis(A1);

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    Mouse.move(xReading, yReading, 0);
    Serial.print(xReading);
    Serial.print("  ");
    Serial.print(yReading);
  }

  // read the mouse button and click or not click:
  // if the mouse button is pressed:
  if (digitalRead(mouseButton) == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      Serial.print("Pressed");
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
      Serial.print("Pressed");
    }
  }

  delay(responseDelay);
}
int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}
void getdisplay(){
    lcd.clear();
    lcd.print("Display");
}

void loop(){
   gettemp();
   getpir();
   getdisplay();
   getmouse();
   getlight();
   getmoisture();
   getsound();
   getsonar();
   getalcohol();
   getvibration();
//   getkey();
}*/

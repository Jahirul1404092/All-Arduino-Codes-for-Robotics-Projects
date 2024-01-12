#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  
  {'3','2','A','3'},
  {'6','5','B','6'},
  {'9','8','C','7'},
  {'#','0','D','*'}
};
byte rowPins[ROWS] = {8, 9, 10,11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1,A0,12,13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}

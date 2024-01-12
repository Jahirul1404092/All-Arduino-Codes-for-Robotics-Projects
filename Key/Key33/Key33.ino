#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'D','0','#','*'},
  {'A','2','3','1'},
  {'B','5','6','4'},
  {'C','8','9','7'}
};
byte rowPins[ROWS] = {0,8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {0,11,12,13}; //connect to the column pinouts of the keypad

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

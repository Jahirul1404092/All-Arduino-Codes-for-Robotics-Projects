#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(6, 7, 2, 3, 4, 5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
const byte ROWS = 3;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

byte rowPins[ROWS] = {11, 12, 13};
byte colPins[COLS] = {8,9,10};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//LiquidCrystal_I2C lcd(0x21, 16, 2);  

void setup(){
  //lcd.backlight();
//  lcd.init(); 
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}

void loop(){
  char customKey = customKeypad.getKey();
  if (customKey){
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(customKey);
  }
}


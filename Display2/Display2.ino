
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(D6, D7, D2, D3, D4, D5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
long i=400;
void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
 Serial.begin(9600);
}
void loop() {
    Serial.print("Value ");
    Serial.println(i);
    delay(100);
    lcd.clear();
    lcd.print("Display"); // Prints "Arduino" on the LCD 
    Serial.println("Display");
    lcd.setCursor(2,1); // Sets the location at which subsequent text written to the LCD will be displayed 
    lcd.print(i); 
}

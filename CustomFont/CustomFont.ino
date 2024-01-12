
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(12, 11, 24, 25, 26, 27); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

void setup() { 
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  Serial.begin(9600);
  
}

void loop() {

//    lcd.clear();
//    lcd.setCursor(1,0);
//    lcd.print("j");
//    delay(1000);

    byte smiley[8] = {
        B00000,
        B10001,
        B00000,
        B00000,
        B10001,
        B01110,
        B00000,
      };
      byte sad[8] = {
        B00000,
        B10001,
        B00000,
        B11111,
        B10001,
        B01110,
        B00000,
      };
      byte s2[8] = {
        B00000,
        B10001,
        B00000,
        B00000,
        B10001,
        B01110,
        B00000,
      };
      byte s1[8] = {
        B11111,
        B10001,
        B00000,
        B11111,
        B10001,
        B01110,
        B00000,
      };
      byte s3[8] = {
        B00011,
        B10001,
        B00000,
        B00000,
        B10001,
        B01110,
        B00000,
      };
      byte s4[8] = {
        B00000,
        B10001,
        B00000,
        B11111,
        B10001,
        B01110,
        B00111,
      };byte s5[8] = {
        B00000,
        B10001,
        B00000,
        B00000,
        B10001,
        B01110,
        B11100,
      };
      byte s6[8] = {
        B00000,
        B10001,
        B00000,
        B00011,
        B10001,
        B01110,
        B00000,
      };
      byte s7[8] = {
        B00000,
        B10001,
        B00000,
        B11111,
        B00001,
        B01110,
        B00001,
      };byte s8[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
      };
      byte s9[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
      };
      byte s10[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
      };

      
  lcd.createChar(0, smiley);
  lcd.createChar(1, sad); 
  lcd.createChar(2, s1);
  lcd.createChar(3, s2); 
  lcd.createChar(4, s3);
  lcd.createChar(5, s4); 
  lcd.createChar(6, s5);
  lcd.createChar(7, s6); 
  lcd.createChar(8, s7);
  lcd.createChar(9, s8); 
  lcd.createChar(10, s10); 
  
  lcd.begin(1, 0);
  
  lcd.autoscroll(); 
  
  lcd.write(byte(1));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
  lcd.write(byte(8));
  lcd.write(byte(9));

  lcd.write(byte(1));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
  lcd.write(byte(8));
  lcd.write(byte(9));

  lcd.write(byte(1));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
  lcd.write(byte(8));
  lcd.write(byte(9));

  lcd.write(byte(1));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
  lcd.write(byte(8));
  lcd.write(byte(9));
  lcd.write(byte(10));
  lcd.write(byte(1));
  lcd.write(byte(0));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
  lcd.write(byte(8));
  lcd.write(byte(9));
  lcd.write(byte(10));
  delay(10000);
}

#include "DigiKeyboard.h"
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(5000);
  DigiKeyboard.sendKeyStroke(0,MOD_GUI_LEFT);
  DigiKeyboard.print("%appdata%");
  DigiKeyboard.delay(200);
  //DigiKeyboard.sendKeyStroke(KEY_ENTER,MOD_CONTROL_LEFT|MOD_SHIFT_LEFT);
//  DigiKeyboard.delay(1000);
//  DigiKeyboard.sendKeyStroke(KET_ARROW_LEFT);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(200);
  
}

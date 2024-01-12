int i=10;
int j=0;
#include "Keyboard.h"
  void typeKey(int key)
  {
    Keyboard.press(key);
    delay(50);
    Keyboard.release(key);
  }
  
  void setup()
  {
    // Begining the Keyboard stream
    Keyboard.begin();
  
    // Wait 500ms
    delay(500);
    
    delay(1000);
  
    typeKey(KEY_RETURN);
 
    delay(1000);
    // Ending streamnotep
    Keyboard.end();

    while(true){
      j++;
      if(i==0){
        break;
        }
      if(j==100){
          Keyboard.press('j');
          delay(50);
          Keyboard.release('j');
          delay(300);
          Keyboard.press('l');
          delay(50);
          Keyboard.release('l');
          delay(700);
          typeKey(KEY_RETURN);
          delay(1500);
          i--;
          }
          Keyboard.end();}
      }

  /* Unused endless loop */
  void loop() {}

/////////////////////////////////////////////////////////////////IDIDIDIDIDIDIDDIDIDIDIDID
long Password1=2233768;//Please type the card's ID number
long Password2=3363317;//Please type the card's ID number
long Password3=7927290;//Please type the card's ID number
const char room_password[]="938CD";
int pass_input_time=50;
int flag=0,RX_Flag=0;//serial port sign
char Code[14]; 
long Num=0;//decode data
int serpin=7;//pin of servo
int Door=0;
int lock=0;
int c=0;
long tim;
long Time=1000; //// dorja bondho korar kotokhoner moddhe khulbe na othoba  3 ta stored value khauar somoy
long Tim=1000;  //// asolei dorja lagche naki check korar somoy
long charge_time;
long charge_time_interval=60000;///////////////////////////////////////////////////////////kotokhon por por charge hobe. 1 day=86400000ms
int charge_sw=A5;
long charging_time=3600000;///////////////////////////////////////////////////////////////////kotokhon charge hobe
long charging_start_time;
int door_open_sw = A4;  // This is our input pin

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(6, 7, 2, 3, 4, 5); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
#include <Servo.h>
Servo name_servo;
 
int servo_position = 0;
/////////////////////////////obstacle
int isObstaclePin = A2;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
///////////////////////////////////////////////////////////////Key4*4
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

/////////////////////////////////////////////////////////////////////////////


void setup() { 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
 Serial.begin(9600);
 name_servo.attach (A4);
 ///////////////////////////////IDSCANNER
   pinMode(13,OUTPUT);
  pinMode(serpin,OUTPUT);
  pinMode(charge_sw, OUTPUT); 
  pinMode(door_open_sw,INPUT);
  Serial.begin(9600);
////////////////////////////////OBSTACLE
  pinMode(isObstaclePin, INPUT);
  charge_time=millis();
}



/////////////////////////////////////////////////////another function for ID card _scanner
void Read_ID(void)
{
    int i=0;
    char temp;
    for(i=0;(Serial.available()>0);i++)//
    {
      temp=Serial.read();
      
   //   Serial.print("temp");
   //   Serial.print(temp);
      delay(2);
   //   Serial.println(i);
      if(temp==0X02)  //recieve the ssrt bit
        {
         flag=1;i=0;RX_Flag=0;//
        }
      if(flag==1)//detect the start bit and recieve data
      {
        if(temp==0X03)//detect the end code,
        {
         flag=0;  //zero clearing
         if(i==13) RX_Flag=1;//
         else RX_Flag=0;
       break;
        }
         Code[i]=temp;
      } 
    }       
     flag=0;//
}


void loop()
{

  int i;
  long temp=0,time=0;
  RX_Flag=0;
  while(1)
  {
   Read_ID();
  if(RX_Flag==1)
  {
    for(i=5;i<11;i++)//
    {
      Num<<=4;
        if(Code[i]>64)  Num+=((Code[i])-55);
        else Num+=((Code[i])-48);
      //  Serial.println(Num);
    }    
    Serial.println(Num);    
  if((Num==Password1)||(Num==Password2))
  {
      
   }
    while(Serial.read()>0);//
    RX_Flag=0;//
    Num=0;//
   }   
  }

  
}

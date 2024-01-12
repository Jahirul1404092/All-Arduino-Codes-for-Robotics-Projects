
/////////////////////////////////////////////////////////////////IDIDIDIDIDIDIDDIDIDIDIDID
long Password1=11402124;//Please type the card's ID number
long Password2=7927290;//Please type the card's ID number
int flag=0,RX_Flag=0;//serial port sign
char Code[14]; 
long Num=0;//decode data
int serpin=7;//pin of servo
int Door=0;

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

void pulse( int serpin,int angle)
{
  int width;//
  width=(angle*11)+500;//
  digitalWrite(serpin,HIGH);//
  delayMicroseconds(width);//
  digitalWrite(serpin,LOW);//
  delay(20-width/1000);
}

void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(serpin,OUTPUT);
  Serial.begin(9600);
  Serial.println("This is a test for access control system");
  delay(100);
  Serial.println(Password1);
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
      digitalWrite(13,HIGH);
      delay(5);
      for(int i=0;i<=50;i++)//
     {
        pulse(serpin,20);// 
      }
      delay(2000);
      while(analogRead(Door)>400);
      delay(1000);
      digitalWrite(13,LOW);
      delay(5);
      for(int i=0;i<=50;i++)//
     {
        pulse(serpin,180);//
      }
   }
    while(Serial.read()>0);//
    RX_Flag=0;//
    Num=0;//
   }   
  }
}

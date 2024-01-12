char mystr[1050]; //Initialized variable to store recieved data
void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(19200);
}

void loop() {
  char str[1050]={};
  bool assign=false;
  Serial.readBytes(mystr,50); //Read the serial data and store in var
  Serial.print("mystr: ");
  Serial.println(mystr); //Print data on Serial Monitor
  delay(1000);
for(int i=0,j=0;i<50;i++){
      if(mystr[i]=='y' && mystr[i+1]=='y'){
          assign=true;
          i+=2;
        }
      if(mystr[i]=='z'&& mystr[i+1]=='z'){
          assign=false;
          break;
        }
      if(assign==true){
        str[j]=mystr[i];
          j++;
       }
    }
    Serial.print(str);
  Serial.println();
}

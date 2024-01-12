#include "rdm630.h"

rdm630 rfid(0, 0);  //TX-pin of RDM630 connected to Arduino pin 6

void setup()
{
    Serial.begin(9600);  // start serial to PC
    rfid.begin();
}

void loop()
{
    byte data[6];
    byte length;

    if(rfid.available()){
        rfid.getData(data,length);
        Serial.println("Data valid");
        for(int i=0;i<length;i++){
            Serial.print(data[i],HEX);
            Serial.print(" ");
        }
        Serial.println();
        //concatenate the bytes in the data array to one long which can be 
        //rendered as a decimal number
        unsigned long result = 
          ((unsigned long int)data[1]<<24) + 
          ((unsigned long int)data[2]<<16) + 
          ((unsigned long int)data[3]<<8) + 
          data[4];              
        Serial.print("decimal CardID: ");
        Serial.println(result);
    }
}

/*The first output is actually the CardID encoded in hex. So e.g. for a CardID (printed on the card) of 0007616525, you will get the following output: 2 0 74 38 D 0

The leading 2 is the STX symbol (0x2) denoting the beginning of an ID.
The three leading 0s are reduced to one single 0
7438D is the decimal number 7616525 encoded in hex
the trailing 0 is proof that the checksum that was transmitted by the module matches the XOR operation performed by the RDM630 library on the received data.
The second output is the CardID as a decimal number (as printed on the card).*/

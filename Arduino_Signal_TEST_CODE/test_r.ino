#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX(connect TX of esp8266), TX (connect RX of es[8266)
 
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(3, OUTPUT);
 delay(5000);
 }
 
void loop(){
  
 String IncomingString="";
 boolean StringReady = false;
 
 while (mySerial.available()){
   IncomingString=mySerial.readString();
   StringReady= true;
  }
 
  if (StringReady){
    Serial.println("Received String: " + IncomingString);
  
  }
  if (IncomingString.indexOf("1560QW") >= 0){
        digitalWrite(3, HIGH);
  }else if (IncomingString.indexOf("1525QW") >= 0){
        digitalWrite(3, LOW);
  }
  }
 

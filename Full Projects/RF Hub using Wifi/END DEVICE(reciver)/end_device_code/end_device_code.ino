/*
  Simple example for receiving
  
  https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>

int redpin = 47 , bluepin = 45 , greenpin = 43;
int rstate = LOW;
int bstate = LOW;
int gstate = LOW;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  
  digitalWrite(redpin, rstate);
  digitalWrite(bluepin, bstate);
  digitalWrite(greenpin, gstate);
}

void loop() {
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
       
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }
    if (value == 5825) { 
          
          rstate = !rstate;
          digitalWrite(redpin, rstate);      
        }
     if (value == 5836){ 
          
          bstate = !bstate;
          digitalWrite(bluepin, bstate);      
        }
     if (value == 1761){ 
          
          gstate = !gstate;
          digitalWrite(greenpin, gstate);      
        }
    mySwitch.resetAvailable();
  }
   
}

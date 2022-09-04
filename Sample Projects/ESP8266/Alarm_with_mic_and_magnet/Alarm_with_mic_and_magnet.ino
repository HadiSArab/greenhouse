
const int magnet_switch = 51;     // Magnet switch
const int rledPin =  26;      //Red  LED pin
const int bledPin =  28;      //Blue LED Pin
const byte interruptPin = 18;
volatile byte state = LOW;




void setup() {
  // initialize the LED pin as an output:
  pinMode(rledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  // initialize the pushbutton pin as an input:
  pinMode(magnet_switch, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  
  Serial.begin(9600);
}
  void loop(){

    while (digitalRead(magnet_switch) == HIGH || state == LOW)
    {
      

 // ALARM Start
    digitalWrite(rledPin, HIGH);
    delay(50);
    digitalWrite(rledPin,LOW);
    delay(50);
     digitalWrite(rledPin, HIGH);
    delay(50);
    digitalWrite(rledPin,LOW);
    delay(50);
      digitalWrite(bledPin, HIGH);
    delay(50);
    digitalWrite(bledPin,LOW);
    delay(50);
     digitalWrite(bledPin, HIGH);
    delay(50);
    digitalWrite(bledPin,LOW);
    delay(50);
    
   }
  
 
  
} 

void blink() {
  state = HIGH;
}


 



const int magnet_switch = 51;     // Magnet switch
const int rledPin =  26;      //Red  LED pin
const int bledPin =  28;      //Blue LED Pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(rledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(magnet_switch, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
   if (digitalRead(magnet_switch) == HIGH) {
    Serial.println("DOOR OPEN");
for(int i=0;i<20;i++)
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
}
/*  
  
  

const int magnet_switch = 51;     // Magnet switch
const int rledPin =  26;      //Red  LED pin
const int bledPin =  28;      //Blue LED Pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(rledPin, OUTPUT);
  pinMode(bledPin, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(magnet_switch, INPUT_PULLUP);

  Serial.begin(9600);
}
  void loop(){

  if(digitalRead(magnet_switch) == 1)
  {
    Serial.println("DOOR IS OPEN");
    
    while (digitalRead(magnet_switch) == HIGH)
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
  
    digitalWrite(rledPin, LOW);
  
} 
*/


#define Relay 46

void setup()
  {
    Serial.begin(9600);
    pinMode(Relay, OUTPUT);
    digitalWrite (Relay, LOW);
  }

 void loop()
 {
  digitalWrite (Relay,HIGH);
  Serial.println("Relay is on");
  delay(3000);

  digitalWrite (Relay,LOW);
  Serial.println("Relay is off");
  delay(3000);
  }

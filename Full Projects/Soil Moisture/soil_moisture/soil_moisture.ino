#define LED D0
#define Sensor A1 

int i;

void setup() {
    
    Serial.begin(9600);
    pinMode (Sensor, INPUT);
    
}

void loop() {
  i = analogRead(Sensor);
  Serial.print("value = ");
  Serial.print(i);
  Serial.println(" ");

  
  delay(1000);
    
}

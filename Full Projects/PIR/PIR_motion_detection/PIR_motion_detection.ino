
const int Pin=2;
 
void setup() {
    pinMode(Pin, INPUT);
    Serial.begin(9600);
}
 
void loop() {
    int sensorValue = digitalRead(Pin);
    if(sensorValue==HIGH){ 
        Serial.println("Detect Motion");
        delay(5000);
        while(sensorValue==LOW){}
    
   }
}

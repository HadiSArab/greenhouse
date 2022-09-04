   /*
  Piezoelectric-Shock-Tap-Sensor-Vibration-Switch-Module
  made on 05 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  https:/
  /electropeak.com/learn/

*/

#define Dig_pin 44
#define LED_pin 50

int Dig_out = LOW;
int Ana_out = 0;
int LED_out = LOW;
 
void setup() {
   Serial.begin(9600);
   pinMode(LED_pin, OUTPUT);
}
 
void loop() {
   Dig_out = digitalRead(Dig_pin)*1000;
   Ana_out = analogRead(A5);

    if(Ana_out > 50)
    {
   Serial.print("Anaolog : ");
   Serial.print(Ana_out);
   Serial.print("       Digital :");
   Dig_out = HIGH;
   Serial.println(Dig_out);
   LED_out = HIGH;
   digitalWrite(LED_pin, LED_out);
   delay(3000);
   LED_out = LOW;
   Dig_out = LOW;
   digitalWrite(LED_pin, LED_out);
   }
    
}

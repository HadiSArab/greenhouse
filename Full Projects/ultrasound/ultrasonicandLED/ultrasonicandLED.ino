#include <HCSR04.h>

byte triggerPin = 28;
byte echoPin = 31;

// All LED pins define here
 
const int greenledPin = 37 ;
const int yelowledPin = 52;
const int redledPin   = 53;

// Variables will change:
int gledState = LOW;
int yledState = LOW;
int rledState = LOW; 

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);

   pinMode(greenledPin, OUTPUT);
   pinMode(yelowledPin, OUTPUT);
   pinMode(redledPin, OUTPUT);
 
}

void loop () {
  double* distances = HCSR04.measureDistanceCm();
  
  Serial.print("1: ");
  Serial.print(distances[0]);
  Serial.println(" cm");
  
  Serial.println("---");
  delay(250);
  
  if (distances[0]>20.00)
   {
      gledState = HIGH;
      yledState = LOW;
      rledState  = LOW;
      digitalWrite(greenledPin, gledState);
      digitalWrite(yelowledPin, yledState);
      digitalWrite(redledPin, rledState);
   }  

  
  if (distances[0]<20.00 & distances[0]>=10.00)
   {
      yledState = HIGH;
      rledState  = LOW;
      digitalWrite(yelowledPin, yledState);
      digitalWrite(redledPin, rledState);
   }  
   else if(distances[0]<20.00 & distances[0]<=10.00)
   {
      yledState = HIGH;
      rledState  = HIGH;
      digitalWrite(yelowledPin, yledState);
      digitalWrite(redledPin, rledState);

      delay(1000);
    
   }

}

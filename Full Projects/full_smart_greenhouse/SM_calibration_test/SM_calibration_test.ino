  /*
Made on Dec 30, 2020
By MehranMaleki @ Electropeak
https://electropeak.com/learn/
*/

#define soil_Pin 33     //AUOT pin on sensor
float value[30]={0.0} ;
float soil_Pin_voltage;

void setup() {
  Serial.begin(115200);
  pinMode(soil_Pin, INPUT);
}

void loop() {
 float s= 0.0 ; 

 for(int i=0;i<30;i++)
 {
   value[i] = analogRead(soil_Pin);
   s+= value[i];
  delay(500);
  Serial.print(value[i]);
  Serial.print("  ");
 }
  soil_Pin_voltage = s/30.0;
  Serial.print("Soil Moisture Sensor Voltage: ");
  Serial.print(soil_Pin_voltage);       //display sensor output votage
  Serial.println(" V");
  
  delay(1000);
}

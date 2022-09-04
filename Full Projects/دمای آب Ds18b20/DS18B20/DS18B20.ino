/*
  DS18B20 Temperature Sensor
  modified on 08 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  https://electropeak.com/learn/
*/

#include <OneWire.h>
#include <DallasTemperature.h>

// Connect Sensor output to pin2
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/*
   The setup function. We only start the sensors here
*/
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
}

void loop(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  float temp = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (temp != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature of Sensor 0 is: ");
    Serial.println(temp);
  }
  else
  {
    Serial.println("Error to reading data");
  }
}

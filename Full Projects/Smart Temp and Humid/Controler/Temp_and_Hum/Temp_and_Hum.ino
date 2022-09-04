
#include "DHT.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


#define DHTPIN 4
#define LED  D2 
#define DHTTYPE DHT11 
#define node_id  46785001
#define LDRPin   A0
 
////////////////////////////////////////////////////////////
// variables 
///////////////////////////////////////////////////////////
const char* ssid     = "EKALAA"; 
const char* password = "Eci@co2263"; 
const char* host = "bsalam.ir"; 

DHT dht(DHTPIN,DHTTYPE); 
float humidityData; 
float temperatureData; 
int device_status1;


int LDR;                    // variable for store photo resistor value

void setup() { 

  Serial.begin(9600); 

  delay(10); 

   dht.begin();

  pinMode(LED, OUTPUT); 

  digitalWrite(LED, LOW); 

   

  // We start by connecting to a WiFi network 

  

  Serial.println(); 

  Serial.println(); 

  Serial.print("Connecting to "); 

  Serial.println(ssid); 

  

  WiFi.begin(ssid, password); //works! 

  

  while (WiFi.status() != WL_CONNECTED) { 

    delay(500); 

    Serial.print("."); 

  } 

  

  Serial.println(""); 

  Serial.println("WiFi connected");   

  Serial.println("IP address: "); 

  Serial.println(WiFi.localIP()); 

} 

  

int value = 0; 

  

void loop() { 


  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));


 /*
    reading LDR sensor value 
 */

  LDR = analogRead(LDRPin);
//float LDRValue = LDR * (5.0/1023.0);                  // if you want to convert the value to voltage , put this line to the code


  /*
   *  connecting to server and send data
   * */

   
  Serial.print("connecting to "); 

  Serial.println(host); 

  

  // Use WiFiClient class to create TCP connections 

  WiFiClient client; 

  const int httpPort = 80; 

  if (!client.connect(host, httpPort)) { //works! 

    Serial.println("connection failed"); 

    return; 

  } 

  

  // We now create a URI for the request 

  if (client.connect(host, 80)) {  
 

    // Make a HTTP request: 

    Serial.print("GET /temperature/dht11.php?node_id="); 

    client.print("GET /temperature/dht11.php?node_id=");     //YOUR URL 

    Serial.println(node_id); 

    client.print(node_id); 

    client.print("&humidity="); 

    Serial.println("&humidity="); 

    client.print(h); 

    Serial.println(h);
    
    client.print("&temperature="); 

    Serial.println("&temperature="); 

    client.print(t); 

    Serial.println(t);
 
    client.print("&hindex="); 

    Serial.println("&hindex="); 

    client.print(hic); 

    Serial.println(hic);

    client.print("&ldr=");
    
    Serial.println("&ldr=");
    
    client.print(LDR);

    Serial.println(LDR);
    
    Serial.print(" ");      //SPACE BEFORE HTTP/1.1 

    Serial.print("HTTP/1.1"); 

    Serial.println(); 

    Serial.println("Host: https://bsalam.ir"); 

    Serial.println("Connection: close"); 

    Serial.println(); 

     

    client.print(" ");      //SPACE BEFORE HTTP/1.1 

    client.print("HTTP/1.1"); 

    client.println(); 

    client.println("Host: bsalam.ir"); 

    client.println("Connection: close"); 

    client.println();

  }
   delay(60000);
}

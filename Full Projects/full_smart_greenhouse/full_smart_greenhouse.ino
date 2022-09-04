/*
  Green House Controller
*/

#include "DHT.h"
#include <OneWire.h>      
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define Trig         25     
#define Echo         36     
#define DHTPIN       4      
#define LDR          34     
#define SM1_PIN      32 
#define SM2_PIN      35
#define SM3_PIN      33   
#define oneWireBus   26     
#define VibPin       14
#define AvibPin      12
#define Relay        5 
#define DHTTYPE DHT11 
int LED = 2;

// Node_ID
const String Node_id = "GH1000";
const char* ssid = "EKALAA";
const char* password = "Eci@co2263";
String serverName = "http://bsalam.ir" ;

// for SM reading array
float value[15]={0.0} ;

//Relay configuration
bool Relay_Status = false ;


int duration;
float distance;
boolean knock = false;
int vib = 0;
int avib =0;
 

DHT dht(DHTPIN, DHTTYPE);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ISR function for Intrrupt comes here .
/// this intrrupt is for vibration alarm or sensing any harmfull strike
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

ICACHE_RAM_ATTR void vibration()
{
  Serial.println("strike detected. . .");
  knock = true;
 // avib = analogRead(AvibPin);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// setup function comes here.
/// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void setup()
{
  Serial.begin(115200);
  dht.begin();
  
  // Start the DS18B20 sensor
  sensors.begin();
  
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(LDR, INPUT);
  pinMode(SM1_PIN, INPUT);
  pinMode(SM2_PIN, INPUT);
  pinMode(SM3_PIN, INPUT);
  pinMode(VibPin, INPUT);
  pinMode(AvibPin, INPUT);
  pinMode(Relay, OUTPUT);
  pinMode(LED, OUTPUT);
  
  digitalWrite(LED, LOW);
  digitalWrite(Relay, LOW);
  
  // intrrupt for vibration alarm
  attachInterrupt(digitalPinToInterrupt(VibPin), vibration, RISING);
 
 // wifi cinnection
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
}



void loop()
{
  Serial.println("\n\n");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// measuring water bank level 
/// "distance" return value but consider that this value show distance from module to water surface 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  digitalWrite (Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration*0.034/2;
  
  // print values
  Serial.print("Distance = ");
  Serial.println(distance);
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Measuring air temp and humidity by DHT11 module with 3 pin , VCC 5v , GND , Digital Output
/// for best result put min 2sec delay between two measurment
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
  // Read Humidity as % 
  float Air_Hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float Air_Temp = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(Air_Hum) || isnan(Air_Temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
   
  }
  
  // print values
  Serial.print(F("Humidity: "));
  Serial.print(Air_Hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(Air_Temp);
  Serial.println(F("°C "));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Vibration alarm variable to server
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  if (knock)
    {
      vib = 1;
      knock = false;
    }
  else
    vib = 0;

  Serial.print("Strike Status = ");
  Serial.print(vib);
  Serial.print("    Strike Level: ");
  Serial.println(avib);
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Measuring Environment Lighting with LDR sensor . in this case we used just simple photo resistor. 
/// resistor should connect to vcc 3.3v and pulldown with 10k resistor
/// in test area we found relation between 10kLUX and 4095 LDR value.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  int LDRRead = analogRead(LDR);
  int Lighting = map(LDRRead, 0, 4095, 0, 10000);
  Serial.print("Lighting = ");
  Serial.println(Lighting);
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Measuring Soil Moisture in three point with three sensor connected via standard socket. 
/// we used Capasitive Soil Moisture Sensor with three outputs. VCC 5v , GND , Digital output
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 int s= 0.0 ; 
 for(int i=0;i<15;i++)
 {
  value[i] = analogRead(SM1_PIN);
  s+= value[i];
  delay(200);
  }
  int SM1Read = s/15 ;
  int SM1 = map(SM1Read, 1990, 2225, 0, 100);
  SM1 = constrain(SM1, 0, 100);
  Serial.print("SoilMoisture1 = ");
  Serial.print(SM1);
  Serial.print("    ");

  s= 0.0 ; 
 for(int i=0;i<15;i++)
 {
  value[i] = analogRead(SM2_PIN);
  s+= value[i];
  delay(200);
  }
  int SM2Read = s/15 ;
  int SM2 = map(SM2Read, 1975, 2190, 0, 100);
  SM2 = constrain(SM2, 0, 100);
  Serial.print("SoilMoisture2 = ");
  Serial.print(SM2);
  Serial.print("    ");

  s= 0.0 ; 
 for(int i=0;i<15;i++)
 {
  value[i] = analogRead(SM3_PIN);
  s+= value[i];
  delay(200);
  }
  int SM3Read = s/15 ;
  int SM3 = map(SM3Read, 2035, 2245, 0, 100);
  SM3 = constrain(SM3, 0, 100);
  Serial.print("SoilMoisture3 = ");
  Serial.print(SM3);
  Serial.print("    ");

  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Water Temp Measuring. 
/// Sensor : DS18B20 water temp sensor , one wire bus protocol ( two library need for this sensor, <OneWire.h> and <DallasTemperature.h>
/// 3 pin : VCC 3.3v , GND , Data . data pin need pullup with 4.7k resistor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 
  sensors.requestTemperatures(); 
  float Water_Temp = sensors.getTempCByIndex(0);
  Serial.print("Water Temperature : ");
  Serial.print(Water_Temp);
  Serial.println("ºC");
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Send data to server using http .
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// HTTP Connection LED Situaltion
  digitalWrite(LED, HIGH);
  delay(30);
  digitalWrite(LED, LOW);
  delay(30);
  digitalWrite(LED, HIGH);
  delay(30);
  digitalWrite(LED, LOW);
  delay(30);
  digitalWrite(LED, HIGH);
  
//Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "/handler/receive.php?TMP=" + String(Air_Temp) +"&HUM="+String(Air_Hum)+"&LDR="+String(Lighting)+"&NID="+String(Node_id)+"&SM1="+String(SM1)+"&SM2="+String(SM2)+"&SM3="+String(SM3)+"&WLV="+String(distance)+"&WTP="+String(Water_Temp)+"&VIB="+String(vib)+"&VIBLEVEL="+String(avib) ;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
  digitalWrite(LED, LOW);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Relay Status checking HTTP request
/// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// HTTP Connection LED Situaltion

for (int l=0; l<20; l++)
{

// LED BLINK
digitalWrite(LED, HIGH);
delay(300);
digitalWrite(LED, LOW);

// Http Connection  
  WiFiClient clientt;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://bsalam.ir/handler/receive.php?NID=GH1000&RL1");  //Specify request destination
    int httpCode1 = http.GET();  
     Serial.println(httpCode1);//Send the request
    if (httpCode1 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Relay_Status = payload.toInt();
//      Serial.print("Air condition situation : ");
//      Serial.print(Relay_Status); //Print the response payload
//      Serial.println();
    }
    
   http.end();
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// relay and led commands.
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  if (Relay_Status == 1)
  {
    digitalWrite(Relay, HIGH);
    Serial.println(" Relay is ON ");
  }
  else if (Relay_Status == 0)
  {
    digitalWrite(Relay, LOW);
    Serial.println(" Relay is OFF ");
  }

  delay(2000);
}

}

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const String NID = "AC1000";

// Set web server port number to 80
WiFiServer server(80);
WiFiClient espClient;

// Set GPIOs for LED and PIR Motion Sensor
const int motionSensor = 4;
const int magnet = 14;
const char* host = "bsalam.ir";

// Variable to store the HTTP request
String header;
int DORStat;
int DORUpd;
int LASTDORUpd =0;
int lastTrigger=0;

// Checks if motion was detected, sets LED HIGH and starts a timer
ICACHE_RAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
   lastTrigger = 1;
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(magnet, INPUT_PULLUP);

  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
 // wifiManager.resetSettings();
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("Access_1000");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();
}

void loop() {
  // Use WiFiClient class to create TCP connections 
  WiFiClient clientt = server.available(); 
  
  
/////////////////////////////////////////////////////////////////////////
//// PIR SITUATION UPDATE
/////////////////////////////////////////////////////////////////////////

 // We now create a URI for the request 
  if(lastTrigger == 1)
  { 
     HTTPClient http;
  if (WiFi.status() == WL_CONNECTED) { //works! 
    http.begin(clientt,"http://bsalam.ir/handler/receive.php?NID=AC1000&PIR=1");  //Specify request destination
    int httpCode1 = http.GET();  
    Serial.println(httpCode1);//Send the request
    }

    http.end();
  }

 lastTrigger = 0; 


/////////////////////////////////////////////////////////////////////////
//// DOOR SITUATION UPDATE
/////////////////////////////////////////////////////////////////////////

  DORUpd = digitalRead(magnet);
if (DORUpd != LASTDORUpd){
  if (DORUpd == HIGH){
  if(WiFi.status() == WL_CONNECTED) {  
   do { 
        HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://bsalam.ir/handler/receive.php?NID=AC1000&DOR=1");  //Specify request destination
    int httpCode1 = http.GET();  
     Serial.println(httpCode1);//Send the request
    if (httpCode1 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      DORStat = payload.toInt();
      Serial.print("DOR Status=");
      Serial.print(DORStat); //Print the response payload
      Serial.println();
    }

    http.end();
   }
  while (DORStat != 1);
  }
 }

if (DORUpd == LOW) {

    if(WiFi.status() == WL_CONNECTED) {  
   do { 
        HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://bsalam.ir/handler/receive.php?NID=AC1000&DOR=0");  //Specify request destination
    int httpCode1 = http.GET();  
     Serial.println(httpCode1);//Send the request
    if (httpCode1 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      DORStat = payload.toInt();
      Serial.print("DOR Status=");
      Serial.print(DORStat); //Print the response payload
      Serial.println();
    }

    http.end();
   }
  while (DORStat != 0);
  }
 }
  LASTDORUpd = DORUpd ;
}
 delay(1000);
}

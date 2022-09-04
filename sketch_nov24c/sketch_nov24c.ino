#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define timeSeconds 10
#define node_id  46785023

// Set web server port number to 80
WiFiServer server(80);
//WiFiClient espClient;

// Set GPIOs for LED and PIR Motion Sensor
const int led1 = 5;
const int led2 = 12;
const int motionSensor = 4;
const int magnet = 14;
const char* host = "bsalam.ir";

// Variable to store the HTTP request
String header;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

// Checks if motion was detected, sets LED HIGH and starts a timer
ICACHE_RAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
 // digitalWrite(led1, HIGH);
 // startTimer = true;
   lastTrigger = 1;

}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(motionSensor, INPUT_PULLUP);
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  // Set LED to LOW
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(magnet, INPUT_PULLUP);

   // WiFiManager
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
  wifiManager.autoConnect("Hadi_Module");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();
}

void loop() {
  // Use WiFiClient class to create TCP connections 
  WiFiClient client; 

  // Current time
 // now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
 // if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
 //   Serial.println("Motion stopped...");
 //   digitalWrite(led1, LOW);
 //   startTimer = false;
 // } 


    // We now create a URI for the request 
if(lastTrigger == 1)
{ 
  if (!client.connect(host, 80)) { //works! 

    Serial.println("connection failed"); 

    return; 
 
  }
  
  if (client.connect(host, 80)) {  
 

    // Make a HTTP request: 

    Serial.print("GET /handler/access.php?node_id="); 

    client.print("GET /handler/access.php?node_id=");     //YOUR URL 

    Serial.println(node_id); 

    client.print(node_id); 

    client.print("&Motion=1"); 

    Serial.println("&Motion=1"); 

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

 lastTrigger = 0; 
}
  
if (digitalRead(magnet) == HIGH) {
    Serial.println("Door opened . . . !");
 
   
  if (!client.connect(host, 80)) { //works! 

    Serial.println("connection failed"); 

    return; 
 
  }

    // We now create a URI for the request 

  if (client.connect(host, 80)) {  
 

    // Make a HTTP request: 

    Serial.print("GET /handler/access.php?node_id="); 

    client.print("GET /handler/access.php?node_id=");     //YOUR URL 

    Serial.println(node_id); 

    client.print(node_id); 

    client.print("&Door=1"); 

    Serial.println("&Door=1"); 

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
    digitalWrite(led2, HIGH);
    while (digitalRead(magnet) == HIGH) {}
  }
  else {
    digitalWrite(led2, LOW);
  }
  
}

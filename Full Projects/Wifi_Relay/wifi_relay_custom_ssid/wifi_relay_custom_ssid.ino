
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


// Set web server port number to 80
WiFiServer server(80);
WiFiClient espClient;

int Relay = 0;
int Relay_status;

// Variable to store the HTTP request
String header;


void setup() {
  Serial.begin(115200);

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  wifiManager.resetSettings();
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("Smart_Relay_1000");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();
}

void loop(){
  WiFiClient clientt = server.available();   // Listen for incoming clients
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://bsalam.ir/handler/receive.php?NID=RL1000&RL1");  //Specify request destination
    int httpCode1 = http.GET();  
     Serial.println(httpCode1);//Send the request
    if (httpCode1 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Relay_status = payload.toInt();
      Serial.print("Device Status=");
      Serial.print(Relay_status); //Print the response payload
      Serial.println();
    }

    http.end();
  }

   if(Relay_status == 0){
     digitalWrite(Relay, LOW);
     Serial.println("Device is ON");  
  }else if(Relay_status == 1){
     digitalWrite(Relay, HIGH);
     Serial.println("Device is OFF");
  }

  delay(1000);
  
 }

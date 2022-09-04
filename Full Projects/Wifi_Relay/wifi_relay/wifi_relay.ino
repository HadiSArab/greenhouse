#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char *ssid = "EKALAA"; //Enter your WIFI ssid 
const char *password = "Eci@co2263"; //Enter your WIFI password 

WiFiClient espClient;

int Relay = 0;
int Relay_status;

void setup()
{
  Serial.begin(115200);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  
  Serial.println("Readings will apear here.");

  WiFi.begin(ssid,password); // Add your Wi-Fi name and password here
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  
}

void loop()
{
    WiFiClient clientt;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://bsalam.ir/relay/device_status.php?did=1");  //Specify request destination
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

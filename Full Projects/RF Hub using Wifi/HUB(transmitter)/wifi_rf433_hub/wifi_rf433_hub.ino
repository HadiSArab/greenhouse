
/*
  Home Automtion Using NodeMCU over a PHP Website
  Visit: https://techzeero.com/iot-projects/home-automation-over-online-server-using-nodemcu-and-php-website
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
static const uint8_t D2   = 4;

 const char* ssid = "Hadi";
 const char* password = "S3cure:%73Admin123!@#";

 int device1_pin=D0;
 int device2_pin=D1;
 int device3_pin=D2;
 int device4_pin=D3;

 int last1 , last2 , last3 , last4 ;
 
 int device_status1;
 int device_status2;
 int device_status3;
 int device_status4;
 
void setup () {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
    
// Transmitter is connected to Arduino Pin #10
    mySwitch.enableTransmit(D2);
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(319);
  }
  
  pinMode(device1_pin,OUTPUT);
  pinMode(device2_pin,OUTPUT);
  pinMode(device3_pin,OUTPUT);
  pinMode(device4_pin,OUTPUT);

}

void loop() {
   WiFiClient clientt;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;  //Declare an object of class HTTPClient
    /*----------------------------------------------*/

    http.begin(clientt,"http://192.168.0.178/automation/device_status.php?did=1");  //Specify request destination
    int httpCode1 = http.GET();  
     Serial.println(httpCode1);//Send the request
    if (httpCode1 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      device_status1 = payload.toInt();
//      Serial.print("Device 1 Status=");
//      Serial.print(device_status1); //Print the response payload
//      Serial.println();
    }
    
    /*----------------------------------------------*/
    
    http.begin(clientt,"http://192.168.0.178/automation/device_status.php?did=2");  //Specify request destination
    int httpCode2 = http.GET();  
     Serial.println(httpCode2);//Send the request
    if (httpCode2 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      device_status2 = payload.toInt();
//      Serial.print("Device 2 Status=");
//      Serial.print(device_status2); //Print the response payload
//      Serial.println();
    }
 
    /*- ---------------------------------------------*/
    
    http.begin(clientt,"http://192.168.0.178/automation/device_status.php?did=3");  //Specify request destination
    int httpCode3 = http.GET(); 
    Serial.println(httpCode3);
    //Send the request
    if (httpCode3 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      device_status3 = payload.toInt();
//      Serial.print("Device 3 Status=");
//      Serial.print(device_status3); //Print the response payload
//      Serial.println();
    }
 
    /*----------------------------------------------*/
    
    http.begin(clientt,"http://192.168.0.178/automation/device_status.php?did=4");  //Specify request destination
    int httpCode4 = http.GET();   
     Serial.println(httpCode4);//Send the request
    if (httpCode4 > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      device_status4 = payload.toInt();
//      Serial.print("Device 4 Status=");
//      Serial.print(device_status4); //Print the response payload
//      Serial.println();
    }
    
    http.end();   //Close connection
  }
  
  if(device_status1 != last1 ){

    last1 = device_status1 ;
    mySwitch.send("011010010001011011001100");
  }
    if(device_status2 != last2 ){

    last2 = device_status2 ;
    mySwitch.send("011010010001011011000001");
  }
    if(device_status3 != last3 ){

    last3 = device_status3 ;
    mySwitch.send("");
  }
    if(device_status4 != last4 ){

    last4 = device_status4 ;
    mySwitch.send("");
  }
 
 
}

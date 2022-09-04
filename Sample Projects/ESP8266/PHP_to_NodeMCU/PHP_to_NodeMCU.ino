
/*
  Home Automtion Using NodeMCU over a PHP Website
  Visit: https://techzeero.com/iot-projects/home-automation-over-online-server-using-nodemcu-and-php-website
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

 const char* ssid = "EKALAA";
 const char* password = "Eci@co2263";

 int device1_pin=D0;
 int device2_pin=D1;
 int device3_pin=D2;
 int device4_pin=D3;
 
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
  
  if(device_status1 == 0){
     digitalWrite(device1_pin,LOW);
     Serial.println("Device 1 ON");  
  }else if(device_status1 == 1){
     digitalWrite(device1_pin,HIGH);
     Serial.println("Device 1 OFF");
  }
  
  if(device_status2 == 0){
     digitalWrite(device2_pin,LOW); 
     Serial.println("Device 2 ON"); 
  }else if(device_status2 == 1){
     digitalWrite(device2_pin,HIGH);
     Serial.println("Device 2 OFF");
  }
  
  if(device_status3 == 0){
     digitalWrite(device3_pin,LOW);
     Serial.println("Device 3 ON");  
  }else if(device_status3 == 1){
     digitalWrite(device3_pin,HIGH);
     Serial.println("Device 3 OFF");
  }
  
  if(device_status4 == 0){
     digitalWrite(device4_pin,LOW);  
     Serial.println("Device 4 ON");
  }else if(device_status4 ==  1){
     digitalWrite(device4_pin,HIGH);
     Serial.println("Device 4 OFF");
  }
 // delay(3000);
}

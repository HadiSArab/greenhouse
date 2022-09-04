#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define TriggerPin  D1
#define EchoPin     D0
#define VibPin      A0
#define Vibration   D5
#define node_id     46785053

#define YLED  D2
#define GLED  D6
#define RLED  D7

const char* ssid     = "EKALAA";                    // Wifi SSID 
const char* password = "Eci@co2263";                // Wifi Password ( nesessary for internet connection)
const char* host = "bsalam.ir";                     // your server domain without "http://"   ( for local server ip " 192.168.x.x ")

// ISR function
ICACHE_RAM_ATTR void vibralarm ()
{
  digitalWrite(YLED, HIGH);
}


void setup() {
// put your setup code here, to run once:
  
  Serial.begin(115200);
  
  pinMode(TriggerPin, OUTPUT);                  // Transmit ultra sound Wave
  pinMode(EchoPin, INPUT);                      // Recieve ultra sound wave
  pinMode(VibPin, INPUT);                       // Analog vibration input pin
  pinMode(Vibration, INPUT);                    // Intrrupt pin for Vibration digital input
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
    
  digitalWrite(YLED, LOW);
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH);

// intrrupt for vibration alarm
  attachInterrupt(digitalPinToInterrupt(Vibration), vibralarm, RISING);

// We start by connecting to a WiFi network 
  Serial.println(); 
  Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); //works!             // Connecting to wifi
  while (WiFi.status() != WL_CONNECTED) {          
  delay(500); 
  Serial.print("."); 
  }
  Serial.println(""); 
  Serial.println("WiFi connected");   
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());                 // print local ip of Node MCU 
}


  void loop() {
  long duration;
  float distance;
  float VibLevel;
  
  digitalWrite(TriggerPin, LOW);                            
  delayMicroseconds(2);

//Set the TriggerPin on HIGH state for 10 microseconds
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

//Read the EchoPin, returning the sound wave travel time in microseconds
  duration = pulseIn(EchoPin, HIGH);

//Calculate the distance
  distance= duration*0.034/2;

//measuring environment vibration level
  VibLevel = analogRead(VibPin);

//LED States Update
  if (distance <= 10)
  {
    digitalWrite(GLED, LOW);
    digitalWrite(RLED, HIGH); 
  }
  else
  {
    digitalWrite(GLED, HIGH);
    digitalWrite(RLED, LOW);
  }
  
//Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("      ");
  Serial.print("Environmental Vibration Level : ");
  Serial.println(VibLevel);

//Connecting to server
  Serial.print("connecting to server");
  Serial.println(host);

// use wificlient class to create TCP connection
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))
  {
    Serial.println("Connection Failed");
    return;
  }

// Now create a URL for the request
  if (client.connect(host, httpPort))
  {
    Serial.print("GET /handler/receive.php?NodeID="); 

    client.print("GET /handler/recieve.php?NodeID=");     //YOUR URL 

    Serial.println(node_id); 

    client.print(node_id); 

    client.print("&VIB="); 

    Serial.println("&VIB="); 

    client.print(VibLevel); 

    Serial.println(VibLevel);
    
    client.print("&DIS="); 

    Serial.println("&DIS="); 

    client.print(distance); 

    Serial.println(distance);
    
    Serial.print(" ");      //SPACE BEFORE HTTP/1.1 

    Serial.print("HTTP/1.1"); 

    Serial.println(); 

    Serial.println("Host: https://bsalam.ir"); 

    Serial.println("Connection: close"); 

    Serial.println(); 

  }
  delay(30000);  
  digitalWrite(YLED, LOW);
 }

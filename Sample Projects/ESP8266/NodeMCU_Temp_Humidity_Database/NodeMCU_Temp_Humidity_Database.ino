#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN D2
#define LED    D6
#define DHTTYPE DHT11

const char* ssid     = "EKALAA";
const char* password = "Eci@co2263";
//void cheshmak(int , int );
const char* host = "192.168.195.139";
DHT dht(DHTPIN,DHTTYPE);
float humidityData;
float temperatureData;




void setup() {
  Serial.begin(9600);
  delay(10);

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
  delay(5000);
  ++value;
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature();
  delay(30000);
  
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
    Serial.print("connected for");
    Serial.print(value);
    Serial.println("th Time");
  //  cheshmak(LED, 10);
    // Make a HTTP request:
    Serial.print("GET /hadisanat/dht11.php?humidity=");
    client.print("GET /hadisanat/dht11.php?humidity=");     //YOUR URL
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    Serial.print(" ");      //SPACE BEFORE HTTP/1.1
    Serial.print("HTTP/1.1");
    Serial.println();
    Serial.println("Host: 192.168.195.139");
    Serial.println("Connection: close");
    Serial.println();
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.195.139");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void cheshmak(int pin, int number)
 {  
  for(int i=1;i<number; i++)
  {
    digitalWrite(pin,HIGH);
    delay(2);
    digitalWrite(pin,LOW);
    delay(2);
    digitalWrite(pin,HIGH);
    delay(2);
    digitalWrite(pin,LOW);
    delay(2);
  }
 }
 

#include <Arduino.h>
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char *WIFI_SSID = "EKALAA";
const char *WIFI_PASSWORD = "Eci@co2263";
const char *URL = "http://httpbin.org/post";
 
WiFiClient client;
HTTPClient httpClient;
 
void setup()
{
    Serial.begin(9600);
 
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("Connected");
    Serial.println(WiFi.localIP());
    
}
 
void loop()
{
    String data = "name=John&age=20";
 
    httpClient.begin(client, URL);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpClient.POST(data);
    String content = httpClient.getString();
    httpClient.end();
 
    Serial.println(content);
    delay(5000);
}

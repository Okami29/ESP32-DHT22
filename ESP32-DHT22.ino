/* ESP32 Code (Arduino IDE) */

#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
#define LEDPIN 2

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

const char *ssid = "ESP32_AccessPoint";
const char *password = "123456789";

float humidityLowThreshold = 30.0;
float humidityHighThreshold = 70.0;

void setup() {
    Serial.begin(115200);
    dht.begin();
    pinMode(LEDPIN, OUTPUT);
    
    WiFi.softAP(ssid, password);
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", index_html);
    });
    server.on("/data", HTTP_GET, []() {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        String humidityStatus = "normal";
        
        if (humidity < humidityLowThreshold) {
            humidityStatus = "low";
            digitalWrite(LEDPIN, HIGH);
        } else if (humidity > humidityHighThreshold) {
            humidityStatus = "high";
            digitalWrite(LEDPIN, HIGH);
        } else {
            digitalWrite(LEDPIN, LOW);
        }
        
        String json = "{";
        json += "\"temperature\":" + String(temperature) + ",";
        json += "\"humidity\":" + String(humidity) + ",";
        json += "\"humidityStatus\":\"" + humidityStatus + "\"";
        json += "}";
        
        server.send(200, "application/json", json);
    });
    
    server.begin();
}

void loop() {
    server.handleClient();
}

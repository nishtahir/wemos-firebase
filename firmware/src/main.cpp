#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"
#include "DHT.h"

#include "FireBaseHttpClient.h"

#define DHTPIN D1
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
FirebaseHttpClient httpClient(FIREBASE_HOST, FIREBASE_AUTH_TOKEN);

void startSerial() {
    Serial.begin(115200);
    delay(10);
    Serial.println("Starting Serial...");
    Serial.println();
    Serial.println();

}

void startWifi() {
    Serial.print("Connecting to SSID: ");
    Serial.println(SSID_NAME);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_NAME, SSID_PASSWORD);
  
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {    
    startSerial();
    startWifi();
    dht.begin();
}

void loop() {

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature(/*isFahrenheit=*/true);
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    float heatIndex = dht.computeHeatIndex(temperature, humidity);

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["temperature"] = temperature;
    root["humidity"] = humidity;
    root["heat"] = heatIndex;

    char buffer[200];
    root.printTo(buffer, sizeof(buffer));
    
    String response = "";
    int statusCode = httpClient.put("/node.json", String(buffer).c_str(), &response);
    if (statusCode != 200) {
        Serial.print("Server error: ");
        Serial.println(statusCode);
        Serial.print("Response body: ");
        Serial.println(response);
    }
    delay(1000);
}
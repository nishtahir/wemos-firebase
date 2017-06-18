#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"

#include "FireBaseHttpClient.h"



FirebaseHttpClient httpClient = FirebaseHttpClient(FIREBASE_HOST, FIREBASE_AUTH_TOKEN);

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

void parseNode(const char* json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    int humidity = root["humidity"];
    int temperature = root["temperature"];

    if(humidity != 0){
        digitalWrite(BUILTIN_LED, HIGH);
    } else {
        digitalWrite(BUILTIN_LED, LOW);
    }
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    
    startSerial();
    startWifi();
}

void loop() {
    String response = "";
    int statusCode = httpClient.get("/node.json", &response);
    if (statusCode == 200) {
        parseNode(response.c_str());
    } else {
        Serial.print("Server error: ");
        Serial.println(statusCode);
        Serial.print("Response body: ");
        Serial.println(response);
    }
    delay(1000);
}
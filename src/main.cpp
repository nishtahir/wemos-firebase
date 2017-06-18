#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

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

void setup() {
    startSerial();
    startWifi();

    String response = "";
    int statusCode = httpClient.get("/test.json", &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
}

void loop() {

}
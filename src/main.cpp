#include <Arduino.h>
#include <EEPROM.h>
#include <FastLED.h>

#include "WiFi.h"

#define NUM_LEDS 1
#define DATA_PIN_ONBOARD 5
#define PIN_TO_SENSOR 26

#define EEPROM_ADDRESS 0
#define EEPROM_VARIABLE_SIZE 35
#define EEPROM_TOTAL_SIZE 2 * EEPROM_VARIABLE_SIZE

#define SERVER_HOST "192.168.10.230"
#define SERVER_PORT 9432

CRGB leds[NUM_LEDS];
int pinStateCurrent = LOW;   // current state of pin
int pinStatePrevious = LOW;  // previous state of pin

char ssidEeprom[EEPROM_VARIABLE_SIZE] = "NA";
char passwordEeprom[EEPROM_VARIABLE_SIZE] = "NA";

void readWifiSettings() {
    EEPROM.begin(EEPROM_TOTAL_SIZE);
    delay(10);
    EEPROM.readBytes(EEPROM_ADDRESS, ssidEeprom, EEPROM_VARIABLE_SIZE);
    EEPROM.readBytes(EEPROM_ADDRESS + EEPROM_VARIABLE_SIZE, passwordEeprom, EEPROM_VARIABLE_SIZE);
    EEPROM.end();
}

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssidEeprom, passwordEeprom);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
        leds[0] = CRGB::Red;
        FastLED.show(100);
        delay(500);
        FastLED.clearData();
    }
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(921600);
    readWifiSettings();
    pinMode(PIN_TO_SENSOR, INPUT);
    FastLED.addLeds<NEOPIXEL, DATA_PIN_ONBOARD>(leds, NUM_LEDS);  // GRB ordering is assumed
    initWiFi();
    delay(100);
}

void loop() {
    pinStatePrevious = pinStateCurrent;
    pinStateCurrent = digitalRead(PIN_TO_SENSOR);

    if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {  // pin state change: LOW -> HIGH
        Serial.println("Motion detected!");

        WiFiClient client;
        if (!client.connect(SERVER_HOST, SERVER_PORT)) {
            Serial.println("Connection failed.");                        
            leds[0] = CRGB::Red;
            FastLED.show(100);
            delay(500);
            FastLED.clearData();
        }        
        client.write(64);
        leds[0] = CRGB::Blue;
        FastLED.show();
    } else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {  // pin state change: HIGH -> LOW
        Serial.println("Motion stopped!");
        leds[0] = CRGB::Green;
        FastLED.show(100);
    }
}
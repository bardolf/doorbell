// Run this only once - to store the SSID and password

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_ADDRESS 0
#define EEPROM_VARIABLE_SIZE 35
#define EEPROM_TOTAL_SIZE 2 * EEPROM_VARIABLE_SIZE

const char* ssid = "SSID\0";          // ssid ended with \0
const char* password = "PASSWORD\0";  // password ended with \0

char ssidEeprom[EEPROM_VARIABLE_SIZE] = "NA";
char passwordEeprom[EEPROM_VARIABLE_SIZE] = "NA";

void setup() {
    Serial.begin(921600);
    EEPROM.begin(EEPROM_TOTAL_SIZE);
    EEPROM.writeBytes(0, ssid, EEPROM_VARIABLE_SIZE);
    EEPROM.writeBytes(EEPROM_VARIABLE_SIZE, password, EEPROM_VARIABLE_SIZE);
    EEPROM.commit();
    EEPROM.end();    
}

void loop() {
    EEPROM.begin(EEPROM_TOTAL_SIZE);
    delay(10);

    EEPROM.readBytes(EEPROM_ADDRESS, ssidEeprom, EEPROM_VARIABLE_SIZE);
    EEPROM.readBytes(EEPROM_ADDRESS + EEPROM_VARIABLE_SIZE, passwordEeprom, EEPROM_VARIABLE_SIZE);
    EEPROM.end();
    Serial.print(ssidEeprom);
    Serial.print(" - ");
    Serial.println(strlen(ssidEeprom));

    Serial.print(passwordEeprom);
    Serial.print(" - ");
    Serial.println(strlen(passwordEeprom));

    delay(5000);
}
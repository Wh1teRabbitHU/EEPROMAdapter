#include <Arduino.h>

#include <EEPROMAdapter.h>
#include <EEPROMSerial.h>

EEPROM::Adapter adapter = EEPROM::Adapter();
EEPROM::Serial serial = EEPROM::Serial(Serial, adapter);

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(100);

	Serial.println("Waiting for instructions...");
}

void loop() {
	serial.checkAndExecute();

	delay(5);
}
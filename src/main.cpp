#include <Arduino.h>

#include <EEPROMAdapter.h>
#include <EEPROMSerial.h>

EEPROM::Adapter adapter = EEPROM::Adapter();
EEPROM::Serial serial = EEPROM::Serial(Serial, adapter);

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(100);

	Serial.println("Waiting for data...");

	/**
	for (int i = 0; i <= 0b1111111111; i++) {
		adapter.writeChip(i, 0b00000001);
	}

	for (int i = 0; i <= 0b1111111111; i++) {
		Serial.print("Value at address " + (String)i + ": ");
		Serial.println(adapter.readChip(i));
	}
	**/
}

void loop() {
	serial.checkAndExecute();

	delay(5);
}
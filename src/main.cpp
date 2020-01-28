#include <Arduino.h>

#include <EEPROMAdapter.h>

EEPROM::Adapter adapter = EEPROM::Adapter();

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(5000);

	Serial.println("Starting to write");

	for (int i = 0; i <= 0b1111111111; i++) {
		adapter.writeChip(i, 0b00000001);
	}

	for (int i = 0; i <= 0b1111111111; i++) {
		Serial.print("Value at address " + (String)i + ": ");
		Serial.println(adapter.readChip(i));
	}
}

void loop() {
	// put your main code here, to run repeatedly:
}
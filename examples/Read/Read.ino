#include <EEPROMAdapter.h>

EEPROM::Adapter adapter = EEPROM::Adapter();

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(100);
}

void loop() {
	Serial.println("Starting to read data from the EEPROM!");

	for (uint16_t index = 0; index < 4096; index++) {
		uint8_t value = adapter.readChip(index);

		Serial.print("Address: ");
		Serial.print(index);
		Serial.print(" Value: ");
		Serial.println(value);
	}

	Serial.println("Finished reading from the EEPROM!");

	delay(10000);
}
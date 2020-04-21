#include <EEPROMAdapter.h>

EEPROM::Adapter adapter = EEPROM::Adapter();

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(100);
}

void loop() {
	Serial.println("Starting to write data to the EEPROM!");

	uint8_t value = 0;

	for (uint16_t index = 0; index < 4096; index++) {
		if (++value > 255) {
			value = 0;
		}

		adapter.writeChip(index, value);

		Serial.print("Address: ");
		Serial.print(index);
		Serial.print(" Value: ");
		Serial.println(value);
	}

	Serial.println("Finished writing to the EEPROM!");

	delay(10000);
}
#include <EEPROMAdapter.h>
#include <EEPROMSerial.h>

EEPROM::Adapter adapter = EEPROM::Adapter();
EEPROM::Serial serial = EEPROM::Serial(Serial, adapter);

void setup() {
	Serial.begin(9600);

	adapter.init();

	delay(100);
}

void loop() {
	serial.checkAndExecute();

	delay(1);
}

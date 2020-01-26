#include <Arduino.h>

/*
	Arduino Mega 2560 Pinout

	49 RDY		VCC
	47 A12  	46 WE
	45 A7 	 	44 NC
	43 A6 		42 A8
	41 A5 		40 A9
	39 A4 		38 A11
	37 A3 		36 OE
	35 A2 		34 A10
	33 A1 		32 CE
	31 A0 		30 IO7
	29 IO0 		28 IO6
	27 IO1 		26 IO5
	25 IO2		24 IO4
	GND			22 IO3
*/

#define ROM_A0  31
#define ROM_A1  33
#define ROM_A2  35
#define ROM_A3  37
#define ROM_A4  39
#define ROM_A5  41
#define ROM_A6  43
#define ROM_A7  45
#define ROM_A8  42
#define ROM_A9  40
#define ROM_A10 34
#define ROM_A11 38
#define ROM_A12 47

#define ROM_IO0 29
#define ROM_IO1 27
#define ROM_IO2 25
#define ROM_IO3 22
#define ROM_IO4 24
#define ROM_IO5 26
#define ROM_IO6 28
#define ROM_IO7 30

#define ROM_CE  32
#define ROM_OE  36
#define ROM_WE  46
#define ROM_RDY 49
#define ROM_NC  44

#define READ_DELAY 1000
#define WRITE_DELAY 1000

uint8_t addressPins[] = {
	ROM_A0,
	ROM_A1,
	ROM_A2,
	ROM_A3,
	ROM_A4,
	ROM_A5,
	ROM_A6,
	ROM_A7,
	ROM_A8,
	ROM_A9,
	ROM_A10,
	ROM_A11,
	ROM_A12
};

uint8_t ioPins[] = {
	ROM_IO0,
	ROM_IO1,
	ROM_IO2,
	ROM_IO3,
	ROM_IO4,
	ROM_IO5,
	ROM_IO6,
	ROM_IO7
};

void readEnable() {
	digitalWrite(ROM_WE, HIGH);
	digitalWrite(ROM_OE, LOW);
	digitalWrite(ROM_CE, LOW);

	delayMicroseconds(READ_DELAY);
}

void writeEnable() {
	digitalWrite(ROM_WE, LOW);
	digitalWrite(ROM_OE, HIGH);
	digitalWrite(ROM_CE, LOW);

	delayMicroseconds(WRITE_DELAY);
}

void standby() {
	digitalWrite(ROM_WE, HIGH);
	digitalWrite(ROM_OE, HIGH);
	digitalWrite(ROM_CE, HIGH);
}

uint8_t getBit(uint8_t byteValue, int position) {
    return (byteValue >> position) & 1;
} 

uint8_t updateBit(uint8_t byteValue, uint8_t position, uint8_t binaryValue) { 
    uint8_t mask = 1 << position;

    return (byteValue & ~mask) | ((binaryValue << position) & mask); 
} 

void changeIO(uint8_t direction) {
	for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
		pinMode(ioPins[i], direction);
	}
}

void setAddress(uint16_t address) {
	for (uint8_t i = 0; i < sizeof(addressPins) / sizeof(uint8_t); i++) {
		digitalWrite(addressPins[i], getBit(address, i));
	}
}

uint8_t readChip(uint16_t address) {
	changeIO(INPUT);
	setAddress(address);
	readEnable();

	uint8_t value = 0;

	for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
		value = updateBit(value, i, digitalRead(ioPins[i]));
	}

	standby();

	return value;
}

void writeChip(uint16_t address, uint8_t data) {
	setAddress(address);

	for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
		digitalWrite(ioPins[i], getBit(data, i));
	}

	changeIO(OUTPUT);
    writeEnable();

	standby();
}

void setup() {
	Serial.begin(9600);

	standby();
	digitalWrite(ROM_NC, LOW);

	pinMode(ROM_WE, OUTPUT);
	pinMode(ROM_OE, OUTPUT);
	pinMode(ROM_CE, OUTPUT);
	pinMode(ROM_NC, OUTPUT);
	pinMode(ROM_RDY, INPUT);

	for (uint8_t i = 0; i < sizeof(addressPins) / sizeof(uint8_t); i++) {
		pinMode(addressPins[i], OUTPUT);
	}

	changeIO(INPUT);

	delay(5000);

	Serial.println("Starting to write");

	writeChip(0x0, 0b01010101);
	writeChip(0x1, 0b10101010);

	Serial.print("Value at address 0x0: ");
	Serial.println(readChip(0x0), HEX);
	Serial.print("Value at address 0x1: ");
	Serial.println(readChip(0x1), HEX);

/*
	for (int i = 0; i <= 0b1111111111; i++) {
		writeChip(i, 0b00000000);
	}

	for (int i = 0; i <= 0b1111111111; i++) {
		Serial.print("Value at address " + (String)i + ": ");
		Serial.println(readChip(i));
	}

	writeChip(0x0, 0b10000000);
	writeChip(0x1, 0b10000001);
	writeChip(0x2, 0b10000010);
	writeChip(0x3, 0b10000011);

	Serial.print("Value at address 0x0: ");
	Serial.println(readChip(0x0));
	Serial.print("Value at address 0x1: ");
	Serial.println(readChip(0x1));
	Serial.print("Value at address 0x2: ");
	Serial.println(readChip(0x2));
	Serial.print("Value at address 0x3: ");
	Serial.println(readChip(0x3));
	*/
}

void loop() {
	// put your main code here, to run repeatedly:
}
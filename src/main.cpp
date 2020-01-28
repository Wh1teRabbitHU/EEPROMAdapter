#include <Arduino.h>

/*
	Arduino Mega 2560 Pinout

	23 RDY		VCC
	25 A12  	24 WE
	27 A7 	 	26 NC
	29 A6 		28 A8
	31 A5 		30 A9
	33 A4 		32 A11
	35 A3 		34 OE
	37 A2 		36 A10
	39 A1 		38 CE
	41 A0 		40 IO7
	43 IO0 		42 IO6
	45 IO1 		44 IO5
	47 IO2		46 IO4
	GND			48 IO3
*/

#define ROM_A0  41
#define ROM_A1  39
#define ROM_A2  37
#define ROM_A3  35
#define ROM_A4  33
#define ROM_A5  31
#define ROM_A6  29
#define ROM_A7  27
#define ROM_A8  28
#define ROM_A9  30
#define ROM_A10 36
#define ROM_A11 32
#define ROM_A12 25

#define ROM_IO0 43
#define ROM_IO1 45
#define ROM_IO2 47
#define ROM_IO3 48
#define ROM_IO4 46
#define ROM_IO5 44
#define ROM_IO6 42
#define ROM_IO7 40

#define ROM_CE  38
#define ROM_OE  34
#define ROM_WE  24
#define ROM_RDY 23
#define ROM_NC  26

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

	for (int i = 0; i <= 0b1111111111; i++) {
		writeChip(i, 0b00000000);
	}

	for (int i = 0; i <= 0b1111111111; i++) {
		Serial.print("Value at address " + (String)i + ": ");
		Serial.println(readChip(i));
	}
}

void loop() {
	// put your main code here, to run repeatedly:
}
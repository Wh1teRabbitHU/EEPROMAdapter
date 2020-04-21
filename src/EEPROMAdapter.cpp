#include "EEPROMAdapter.h"

namespace EEPROM {

    Adapter::Adapter() {
    }

    Adapter::~Adapter() {

    }

    void Adapter::init() {
        standby();
        digitalWrite(ROM_NC, LOW);

        pinMode(ROM_WE, OUTPUT);
        pinMode(ROM_OE, OUTPUT);
        pinMode(ROM_CE, OUTPUT);
        pinMode(ROM_NC, OUTPUT);
        pinMode(ROM_RDY, INPUT);

        pinMode(IND_LED, OUTPUT);

        for (uint8_t i = 0; i < sizeof(addressPins) / sizeof(uint8_t); i++) {
            pinMode(addressPins[i], OUTPUT);
        }

        changeIO(INPUT);
    }

    uint8_t Adapter::readChip(uint16_t address) {
        digitalWrite(IND_LED, HIGH);
        
        changeIO(INPUT);
        setAddress(address);
        readEnable();

        uint8_t value = 0;

        for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
            value = updateBit(value, i, digitalRead(ioPins[i]));
        }

        standby();

        digitalWrite(IND_LED, LOW);

        return value;
    }

    void Adapter::writeChip(uint16_t address, uint8_t data) {
        digitalWrite(IND_LED, HIGH);

        setAddress(address);

        for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
            digitalWrite(ioPins[i], getBit(data, i));
        }

        changeIO(OUTPUT);
        writeEnable();

        standby();

        digitalWrite(IND_LED, LOW);
    }

    void Adapter::readEnable() {
        digitalWrite(ROM_WE, HIGH);
        digitalWrite(ROM_OE, LOW);
        digitalWrite(ROM_CE, LOW);

        delayMicroseconds(READ_DELAY);
    }

    void Adapter::writeEnable() {
        digitalWrite(ROM_WE, LOW);
        digitalWrite(ROM_OE, HIGH);
        digitalWrite(ROM_CE, LOW);

        delayMicroseconds(WRITE_DELAY);
    }

    void Adapter::standby() {
        digitalWrite(ROM_WE, HIGH);
        digitalWrite(ROM_OE, HIGH);
        digitalWrite(ROM_CE, HIGH);
    }

    uint8_t Adapter::getBit(uint8_t byteValue, int position) {
        return (byteValue >> position) & 1;
    } 

    uint8_t Adapter::updateBit(uint8_t byteValue, uint8_t position, uint8_t binaryValue) { 
        uint8_t mask = 1 << position;

        return (byteValue & ~mask) | ((binaryValue << position) & mask); 
    } 

    void Adapter::changeIO(uint8_t direction) {
        for (uint8_t i = 0; i < sizeof(ioPins) / sizeof(uint8_t); i++) {
            pinMode(ioPins[i], direction);
        }
    }

    void Adapter::setAddress(uint16_t address) {
        for (uint8_t i = 0; i < sizeof(addressPins) / sizeof(uint8_t); i++) {
            digitalWrite(addressPins[i], getBit(address, i));
        }
    }
}
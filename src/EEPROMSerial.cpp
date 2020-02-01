#include "EEPROMSerial.h"

namespace EEPROM {

    Serial::Serial(Stream &inAndOut, EEPROM::Adapter &adapter) {
        serialIn = &inAndOut;
        serialOut = &inAndOut;
        eepromAdapter = &adapter;
    }

    Serial::Serial(Stream &in, Stream &out, EEPROM::Adapter &adapter) {
        serialIn = &in;
        serialOut = &out;
        eepromAdapter = &adapter;
    }

    Serial::~Serial() {}

    void Serial::checkAndExecute() {
        if (!serialIn->available()) {
            return;
        }

        char flag = serialIn->read();
        uint16_t address;
        uint8_t value;

        switch (tolower(flag)) {
            case READ_FLAG:
                address = readNumber(ADDRESS_LENGTH);

                readMemory(address);

                break;
            case WRITE_FLAG:
                address = readNumber(ADDRESS_LENGTH);
                value = readNumber(VALUE_LENGTH);

                writeMemory(address, value);

                break;
            default:
                serialOut->println("Unknown flag: " + flag);

                break;
        }
    }

    uint16_t Serial::readNumber(int size) {
        while (!serialIn->available()); // Wait for data to comes in

        int number = serialIn->read() - '0';

        if (size-- > 1) {
            return number * lround(pow(10, size)) + readNumber(size);
        }

        return number;
    }

    void Serial::readMemory(uint16_t address) {
        uint8_t value = eepromAdapter->readChip(address);

        serialOut->println("Read data from memory: ");
        serialOut->print(address);
        serialOut->print("=");
        serialOut->println(value);
    }

    void Serial::writeMemory(uint16_t address, uint8_t value) {
        serialOut->println("Write data to memory: ");
        serialOut->print(address);
        serialOut->print("=");
        serialOut->println(value);

        eepromAdapter->writeChip(address, value);
    }

}
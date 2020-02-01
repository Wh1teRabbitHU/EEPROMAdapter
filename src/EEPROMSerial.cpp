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

    Serial::~Serial() {

    }

    void Serial::checkAndExecute() {
        if (!serialIn->available()) {
            return;
        }

        flag = serialIn->read();
        address = readNumber(4);
        value = readNumber(2);

        serialOut->println("Received data: ");
        serialOut->print(flag);
        serialOut->print(": ");
        serialOut->print(address);
        serialOut->print("=");
        serialOut->println(value);
    }

    uint16_t Serial::readNumber(int size) {
        while (!serialIn->available()); // Wait for data to comes in

        int number = serialIn->read() - '0';

        if (size-- > 1) {
            return number * lround(pow(10, size)) + readNumber(size);
        }

        return number;
    }

}
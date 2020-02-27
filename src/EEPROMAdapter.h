#ifndef EEPROM_ADAPTER
    #define EEPROM_ADAPTER

    #include "Arduino.h"

    namespace EEPROM {

        /*
            Arduino Mega 2560 Pin layout

            22 RDY		VCC
            24 A12  	23 WE
            26 A7 	 	25 NC
            28 A6 		27 A8
            30 A5 		29 A9
            32 A4 		31 A11
            34 A3 		33 OE
            36 A2 		35 A10
            38 A1 		37 CE
            40 A0 		39 IO7
            42 IO0 		41 IO6
            44 IO1 		43 IO5
            46 IO2		45 IO4
            GND			47 IO3
        */

        #define ROM_A0  40
        #define ROM_A1  38
        #define ROM_A2  36
        #define ROM_A3  34
        #define ROM_A4  32
        #define ROM_A5  30
        #define ROM_A6  28
        #define ROM_A7  26
        #define ROM_A8  27
        #define ROM_A9  29
        #define ROM_A10 35
        #define ROM_A11 31
        #define ROM_A12 24

        #define ROM_IO0 42
        #define ROM_IO1 44
        #define ROM_IO2 46
        #define ROM_IO3 47
        #define ROM_IO4 45
        #define ROM_IO5 43
        #define ROM_IO6 41
        #define ROM_IO7 39

        #define ROM_CE  37
        #define ROM_OE  33
        #define ROM_WE  23
        #define ROM_RDY 22
        #define ROM_NC  25

        #define READ_DELAY 1000
        #define WRITE_DELAY 1000

        class Adapter {
            public:
                // Constructor/destructor
                Adapter();
                virtual ~Adapter();

                // Methods
                void init(void);
                uint8_t readChip(uint16_t address);
                void writeChip(uint16_t address, uint8_t data);

            private:
                uint8_t addressPins[13] = {
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

                uint8_t ioPins[8] = {
                    ROM_IO0,
                    ROM_IO1,
                    ROM_IO2,
                    ROM_IO3,
                    ROM_IO4,
                    ROM_IO5,
                    ROM_IO6,
                    ROM_IO7
                };

                void readEnable(void);
                void writeEnable(void);
                void standby(void);
                uint8_t getBit(uint8_t byteValue, int position);
                uint8_t updateBit(uint8_t byteValue, uint8_t position, uint8_t binaryValue);
                void changeIO(uint8_t direction);
                void setAddress(uint16_t address);
        };
    }

#endif
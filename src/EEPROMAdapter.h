#ifndef EEPROM_ADAPTER
    #define EEPROM_ADAPTER

    #include "Arduino.h"

    namespace EEPROM {

        /*
            Arduino Mega 2560 Pin layout

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

        #ifndef CUSTOM_PINS
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
        #endif

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
#ifndef EEPROM_SERIAL
    #define EEPROM_SERIAL

    #include "Arduino.h"
    #include "EEPROMAdapter.h"

    namespace EEPROM {

        #define READ_FLAG 'r'
        #define WRITE_FLAG 'w'

        #define ADDRESS_LENGTH 4
        #define VALUE_LENGTH 2

        class Serial {
            public:
                // Constructor/destructor
                Serial(Stream &inAndOut, EEPROM::Adapter &adapter);
                Serial(Stream &in, Stream &out, EEPROM::Adapter &adapter);
                virtual ~Serial();

                // Methods
                void checkAndExecute(void);
                
            private:
                Stream* serialIn;
		        Stream* serialOut;
                EEPROM::Adapter* eepromAdapter;

                uint16_t readNumber(int size);
                void readMemory(uint16_t address);
                void writeMemory(uint16_t address, uint8_t value);
        };
    }

#endif
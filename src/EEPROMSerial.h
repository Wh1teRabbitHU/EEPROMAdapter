#ifndef EEPROM_SERIAL
    #define EEPROM_SERIAL

    #include "Arduino.h"
    #include "EEPROMAdapter.h"

    namespace EEPROM {

        class Serial {
            public:
                // Constructor/destructor
                Serial(Stream &inAndOut, EEPROM::Adapter &adapter);
                Serial(Stream &in, Stream &out, EEPROM::Adapter &adapter);
                virtual ~Serial();

                // Methods
                void checkAndExecute(void);
                uint16_t readNumber(int size);

            private:
                Stream* serialIn;
		        Stream* serialOut;
                EEPROM::Adapter* eepromAdapter;

                char flag;
                uint16_t address; 
                uint8_t value;
        };
    }

#endif
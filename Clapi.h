#ifndef Clapi_h
#define Clapi_h

#include "Arduino.h"

#define CMD_HANDSHAKE 0x13

class Clapi {
private:
    void (*listener)(int code, int argsCount, float args[]) = NULL;

protected:
    bool firstParam = true;
    bool initialized = false;
    
    void checkFirstParam() {
        if (firstParam) {
            Serial.print("{");
        } else {
            Serial.print(",");
        }
        firstParam = false;
    }

public:

    void init() {
        Serial.begin(115200);
        Serial.setTimeout(16);
        delay(50); // для корректной работы
        initialized = true;
    }
    
    Clapi* query(const char* key, const char* value);
    Clapi* query(const char* key, const int value);
    Clapi* query(const char* key, const long value);
    Clapi* query(const char* key, const float value);
    Clapi* query(const char* key, const double value);
    Clapi* query(const char* key, const char value);
    Clapi* query(const char* key, const bool value);
    Clapi* query(const char* key, const int array_value[], const int array_size);
    Clapi* query(const char* key, const float array_value[], const int array_size);
    Clapi* response(const int code);
    
    void send();
    void send(const int code);

    void processInput();
    void setMessageListener(void (*listener)(int code, int argsCount, float args[]));
};

#endif

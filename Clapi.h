#ifndef Clapi_h
#define Clapi_h

#include "Arduino.h"

#define CMD_HANDSHAKE 0x13

class Clapi {
private:
    void (*listener)(int code, int argsCount, float args[]) = NULL;
    char* device_id = NULL;

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
    
    void init(const char* device_id) {
        this->device_id = device_id;
        init();
    }
    
    Clapi* query(const char* key, const char* value);
    Clapi* query(const char* key, const int value);
    Clapi* query(const char* key, const long value);
    Clapi* query(const char* key, const float value);
    Clapi* query(const char* key, const double value);
    Clapi* query(const char* key, const char value);
    Clapi* query(const char* key, const bool value);
    Clapi* response(const int code);
    
    void send();

    void processInput();
    void setMessageListener(void (*listener)(int code, int argsCount, float args[]));
    void invokeSystemListener(int code, int argsCount, float args[]);
};

#endif

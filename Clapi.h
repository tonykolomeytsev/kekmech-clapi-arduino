#ifndef Clapi_h
#define Clapi_h

#include "Arduino.h"

class Api {
private:
    void (*listener)(int code, int argsCount, float args[]);

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
    
    void init(int baud_rate = 115200) {
        Serial.begin(baud_rate);
        Serial.setTimeout(16);
        delay(300);
        initialized = true;
    }

    Api* param(const char* key, const char* value);
    Api* param(const char* key, const int value);
    Api* param(const char* key, const long value);
    Api* param(const char* key, const float value);
    Api* param(const char* key, const double value);
    Api* param(const char* key, const char value);
    Api* param(const char* key, const bool value);
    
    void send();

    void processInput();
    void setMessageListener(void (*listener)(int code, int argsCount, float args[]));
};

#endif
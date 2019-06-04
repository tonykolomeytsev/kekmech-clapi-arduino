#include "Arduino.h"
#include "Clapi.h"

Clapi* Clapi::query(const char* key, const char* value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":\"");
    Serial.print(value);
    Serial.print("\"");
    return this;
}

Clapi* Clapi::query(const char* key, const int value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":");
    Serial.print(value, DEC);
    return this;
}

Clapi* Clapi::query(const char* key, const long value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":");
    Serial.print(value, DEC);
    return this;
}

Clapi* Clapi::query(const char* key, const float value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":");
    Serial.print(static_cast<double>(value), 16);
    return this;
}

Clapi* Clapi::query(const char* key, const double value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":");
    Serial.print(value, 16);
    return this;
}

Clapi* Clapi::query(const char* key, const char value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":\"");
    Serial.print(value);
    Serial.print("\"");
    return this;
}

Clapi* Clapi::query(const char* key, const bool value) {
    checkFirstParam();
    Serial.print("\"");
    Serial.print(key);
    Serial.print("\":");
    Serial.print(value ? "true" : "false");
    return this;
}

Clapi* Clapi::response(const int code) {
    checkFirstParam();
    Serial.print("\"code\":");
    Serial.print(code);
    return this;
}

void Clapi::send() {
    Serial.println("}");
    firstParam = true;
}

void Clapi::send(const int code) {
    checkFirstParam();
    Serial.print("\"code\":");
    Serial.print(code);
    Serial.println("}");
    firstParam = true;
}

void Clapi::processInput() {
	  if (!Serial.available()) return;
    // если не проинициализировались, то ничего не делаем
    if (!initialized) return;
    // когда для чтения становится доступно 2 байта, тогда продолжаем
    while (Serial.available() < 2); // waiting
    int code = Serial.read();
    int argsCount = Serial.read();

    if (argsCount == 0) {
        if (listener != NULL) listener(code, argsCount, NULL);
    } else {
         // количество байт, которое займут аргументы функции
        int bytesToWait = argsCount * 4;
        // когда дождёмся всех аргументов, тогда продолжим
        while (Serial.available() < bytesToWait); // waiting

        // выделяем память под массив агрументов
        float *args = new float[argsCount];
        for (int i = 0; i < argsCount; i++) {
            union { char bin[4]; float d; } doubleAsBytes;

            // просто последовательно пихаем 8 байт в double ячейку
            for (int j = 0; j < 4; j++) {
                doubleAsBytes.bin[j] = int(Serial.read());
            }
            // засовываем расшифрованный double в аргументы
            args[i] = doubleAsBytes.d;
        }
        if (listener != NULL) listener(code, argsCount, args);
        delete[] args;
    }
}

void Clapi::setMessageListener(void (*listener)(int code, int argsCount, float args[])) {
    this->listener = listener;
}



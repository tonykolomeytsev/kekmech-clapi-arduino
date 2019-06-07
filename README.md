# Clapi

The library automates the transfer of data between Arduino and Raspberry, which simplifies the control of a robot or other device built on the basis of one Raspberry and several Arduino.

The main ideology of the library is that Raspberry can send Arduino only commands consisting of an array of bytes (to perform control). Arduino can return any feedback in the form of JSON.

![alt text](https://raw.githubusercontent.com/tonykolomeytsev/kekmech-clapi-arduino/master/img.png)

## Installing

Download this repo as .zip and add it to Arduino IDE as new library, like any other library.

## Features

* Receiving request data in binary format
* JSON response to a request with easily add parameters without ugly string concatenations
* Automatic request processing (you don't need to parse input bytes).

## Waiting for request from Raspberry Pi

After the Raspberry Pi sends a message, Arduino should process it with Clapi::processInput(). 

Raspberry Pi can send multiple float arguments.

```
#include <Clapi.h>

// connect to Raspberry Pi via USB
Clapi *api = new Clapi();

// this function will be launched, when message has arrived
void listener(int code, int argsCount, float args[]) {
    if (code == 1) {
        // do something
    }
}

void setup() {
    api->init(); // don't forget INIT
    // you can use lambda intead function reference
    api->setMessageListener(listener);
    // sending device name to raspberry 
    // (only for clapi-raspberry lib v1.0)
    api->query("device_id", "test")->send();
}

void loop() {
    // ...
    // to do something
    // ...
    api->processInput(); // call it as much as possible
}
```

## Create JSON response

Message for raspberry is a JSON.

JSON sending example:

```
api ->query("email", "foo@bar.com")
    ->query("tel", 12345678)
    ->query("is_pressed", false)
    ->send(); // <--- DO NOT FORGET TO WRITE send() !!!
```

The code from the example will send the following line to Raspberry Pi:

```
{
    "email":"foo@bar.com",
    "tel":12345678,
    "is_pressed":false
}
```

You can transfer **int**, **float**, **string**, **char** and **bool** values. Check the Basic.ino sketch in examples.

## License

```
MIT License

Copyright (c) 2019 Anton Kolomeytsev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
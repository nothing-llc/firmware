#ifndef ARDUINO_H
#define ARDUINO_H

#include "insane-binary-constants.h"
#include "pico/stdlib.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

using std::min;
using std::max;

// misc. arduino shit
#define MSBFIRST 0
#define LSBFIRST 1

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define HEX 0

using String = std::string;

class Stream {
public:
	template <typename T>
	void print(const T&, int = 0) { }

	void println() { }
};

extern Stream Serial;

class __FlashStringHelper {};
typedef volatile uint8_t BusIO_PortReg;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int state);

static int digitalPinToPort(int pin) { return 0; }
static BusIO_PortReg* portOutputRegister(int port) { return nullptr; }
static BusIO_PortReg* portInputRegister(int port) { return nullptr; }
static int digitalPinToBitMask(int pin) { return 0; }

static inline void delay(unsigned int ms) {
	sleep_ms(ms);
}

static inline void delayMicroseconds(unsigned long int us) {
	sleep_us(us);
}

static inline void yield() {}

#endif

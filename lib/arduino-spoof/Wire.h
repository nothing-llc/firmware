#ifndef ARDUINO_WIRE_H
#define ARDUINO_WIRE_H

#include "Arduino.h" // lol

class TwoWire {
public:
	TwoWire();

	void begin(uint8_t address = 0);
	void end();
	void beginTransmission(uint8_t address);
	int endTransmission(bool stop = true);

	size_t write(const uint8_t* buffer, size_t length);
	uint8_t read();

	size_t requestFrom(
		uint8_t address,
		size_t quantity,
		bool stop = true
	);
};

extern TwoWire Wire;

#endif

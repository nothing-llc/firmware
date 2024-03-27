#ifndef ARDUINO_WIRE_H
#define ARDUINO_WIRE_H

#include "Arduino.h" // lol

class TwoWire {
	// TODO
public:
	TwoWire() = default;

	void begin(uint8_t address = 0) {}
	void end() {}
	void beginTransmission(uint8_t address) {}
	int endTransmission(bool stop = true) { return 0; }

	size_t write(const uint8_t* buffer, size_t length) { return 0; }
	uint8_t read() { return 0; }

	size_t requestFrom(
		uint8_t address, size_t quantity, bool stop = true
	) { return 0; }
};

extern TwoWire Wire;

#endif

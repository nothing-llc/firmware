#include "Wire.h"

TwoWire::TwoWire() {
}

void TwoWire::begin(uint8_t address) {
}

void TwoWire::end() {
}

void TwoWire::beginTransmission(uint8_t address) {
}

int TwoWire::endTransmission(bool stop) {
	return 0;
}

size_t TwoWire::write(const uint8_t* buffer, size_t length) {
	return 0;
}

uint8_t TwoWire::read() {
	return 0;
}

size_t TwoWire::requestFrom(
	uint8_t address,
	size_t quantity,
	bool stop
) {
	return 0;
}

TwoWire Wire;

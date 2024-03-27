#ifndef ARDUINO_WIRE_H
#define ARDUINO_WIRE_H

#include "Arduino.h" // lol
#include "hardware/i2c.h"
#include <array>
#include <vector>

// XXX: for now...?
#define RADIO_I2C_SDA_PIN 12
#define RADIO_I2C_SCL_PIN 13
#define RADIO_I2C_INSTANCE i2c0

#if !defined(RADIO_I2C_SDA_PIN) && \
    !defined(RADIO_I2C_SCL_PIN) && \
    !defined(RADIO_I2C_INSTANCE)
	#define RADIO_I2C_SDA_PIN PICO_DEFAULT_I2C_SDA_PIN
	#define RADIO_I2C_SCL_PIN PICO_DEFAULT_I2C_SCL_PIN
	#define RADIO_I2C_INSTANCE i2c_default
#endif

class TwoWire {
public:
	constexpr const static size_t buffer_size = 32;
	constexpr const static size_t timeout_us = 1e6;

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

private:
	i2c_inst_t* i2c;

	bool tx_queued;
	uint8_t tx_address;
	std::vector<uint8_t> tx_buffer;
	std::array<uint8_t, buffer_size> rx_buffer;
	uint8_t* read_head;
};

extern TwoWire Wire;

#endif

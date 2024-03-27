#include "Wire.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"

TwoWire::TwoWire()
: i2c(RADIO_I2C_INSTANCE),
  tx_queued{false},
  tx_address{0},
  tx_buffer(buffer_size),
  read_head{nullptr} {}

void TwoWire::begin(uint8_t address) {
	i2c_init(i2c, 100e3); // 100 kHz, ONLY
	gpio_set_function(RADIO_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(RADIO_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(RADIO_I2C_SDA_PIN);
	gpio_pull_up(RADIO_I2C_SCL_PIN);
}

void TwoWire::end() {}

void TwoWire::beginTransmission(uint8_t address) {
	tx_address = address;
	tx_queued = true;
}

int TwoWire::endTransmission(bool stop) {
	if (!tx_queued) return 0;

	int written = i2c_write_timeout_us(
		i2c,
		tx_address,
		tx_buffer.data(),
		tx_buffer.size(),
		!stop,
		timeout_us
	);

	// not sure if these should be called if there's an error; the arduino
	// spec doesn't say what happens with the buffers
	tx_buffer.clear();
	tx_queued = false;

	switch (written) {
	case PICO_ERROR_TIMEOUT:
		return 5; // timeout, arduino spec
	case PICO_ERROR_GENERIC:
		return 4; // other error, arduino spec
	}

	return 0;
}

size_t TwoWire::write(const uint8_t* buffer, size_t length) {
	length = min(length, buffer_size - tx_buffer.size());
	tx_buffer.insert(tx_buffer.end(), buffer, buffer + length);
	return length;
}

uint8_t TwoWire::read() {
	if (read_head && read_head < rx_buffer.end()) {
		return *(read_head++);
	} else return 0;
}

size_t TwoWire::requestFrom(
	uint8_t address,
	size_t quantity,
	bool stop
) {
	quantity = min(quantity, buffer_size);

	int read = i2c_read_timeout_us(
		i2c,
		address,
		rx_buffer.data(),
		quantity,
		!stop,
		timeout_us
	);

	switch (read) {
	case PICO_ERROR_TIMEOUT:
	case PICO_ERROR_GENERIC:
		read_head = nullptr;
		return 0;
	}

	read_head = rx_buffer.data();
	return read;
}

TwoWire Wire;

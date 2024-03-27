#ifndef ARDUINO_SPI_H
#define ARDUINO_SPI_H

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2

class SPISettings {
public:
	template <typename... A>
	SPISettings(A...);
};

class SPIClass {
public:
	void begin() {}

	template<typename... A>
	inline void transfer(A...) {}

	inline void beginTransaction(const SPISettings&) {}
	inline void endTransaction() {}
};

extern SPIClass SPI;

#endif

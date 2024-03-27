add_library(arduino-spoof
	arduino-spoof/Arduino.c++
	arduino-spoof/SPI.c++
	arduino-spoof/Wire.c++
)

target_include_directories(arduino-spoof PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/arduino-spoof/
)

target_link_libraries(arduino-spoof
	pico_stdlib
	hardware_gpio
	hardware_i2c
)

add_library(adafruit-busio
#	Adafruit_BusIO/Adafruit_BusIO_Register.cpp
	Adafruit_BusIO/Adafruit_SPIDevice.cpp
	Adafruit_BusIO/Adafruit_I2CDevice.cpp
)

target_include_directories(adafruit-busio PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Adafruit_BusIO/
)

target_link_libraries(adafruit-busio
	arduino-spoof
)

add_library(adafruit-gfx
#	Adafruit-GFX-Library/Adafruit_SPITFT.cpp
	Adafruit-GFX-Library/Adafruit_GFX.cpp
	Adafruit-GFX-Library/Adafruit_GrayOLED.cpp
)

target_include_directories(adafruit-gfx PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Adafruit-GFX-Library/
)

target_link_libraries(adafruit-gfx
	arduino-spoof
	adafruit-busio
)

add_library(adafruit-ssd1305
	Adafruit_SSD1305/Adafruit_SSD1305.cpp
)

target_include_directories(adafruit-ssd1305 PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Adafruit_SSD1305/
)

target_link_libraries(adafruit-ssd1305
	arduino-spoof
	adafruit-gfx
)


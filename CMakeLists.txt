cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH ../pico-sdk/)

include(pico_sdk_import.cmake)
project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_executable(firmware
	src/ssd1305.c++
)

# unfortunately these have to be up here... ok
add_compile_definitions(
	TEENSYDUINO
	ARDUINO=100
	PROGMEM=
)
add_subdirectory(lib/)

pico_enable_stdio_usb(firmware 1)
pico_enable_stdio_uart(firmware 1)
pico_add_extra_outputs(firmware)

target_link_libraries(firmware
	pico_stdlib
	adafruit-ssd1305
)

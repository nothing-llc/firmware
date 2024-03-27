/*
 * test of I²C SSD1305 display, through manipulated Adafruit libraries.
 * 
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#include "pico/stdlib.h"
#include <cstdio>

#include "Wire.h"
#include "Adafruit_SSD1305.h"

#define OLED_RESET 9 // whatever

// i2c initialization call
Adafruit_SSD1305 display(128, 64, &Wire, OLED_RESET);

// stolen from adafruit!
void display_test() {
	if (!display.begin(0x3C)) {
		printf("Unable to initialize OLED\n");
		return;
	}

	// init done
	display.display(); // show splashscreen
	sleep_ms(1000);
	display.clearDisplay(); // clears the screen and buffer

	// draw a single pixel
	display.drawPixel(10, 10, WHITE);
	display.display();
	sleep_ms(1000);
	display.clearDisplay();
}

int main() {
	stdio_init_all();
	display_test();
	for (;;) tight_loop_contents();
}

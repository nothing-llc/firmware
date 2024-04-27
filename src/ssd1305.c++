/*
 * test of I²C SSD1305 display, through manipulated Adafruit libraries.
 *
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#include "pico/stdlib.h"
#include <cstdio>

#include "Wire.h"
#include "Adafruit_SSD1305.h"
#include "Fonts/FreeMono9pt7b.h"

#define OLED_RESET 9 // whatever

// i2c initialization call
Adafruit_SSD1305 display(128, 64, &Wire, OLED_RESET);

// stolen from adafruit!
void display_test() {
	if (!display.begin(0x3C)) {
		printf("Unable to initialize OLED\n");
		return;
	}

	display.clearDisplay();   // clears the screen and buffer
	display.setFont(&FreeMono9pt7b);
//	display.drawChar(20, 20, 't', WHITE, BLACK, 1);
	display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,20);
//	display.drawPixel(20, 20, WHITE);
	display.println("test");
	display.display();
}

int main() {
	stdio_init_all();
	display_test();
	for (;;) tight_loop_contents();
}

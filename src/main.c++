/*
 * main pico code. pretty self-explanatory, hopefully.
 *
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#include "adc_spi.h"
#include "audio_out.h"
#include "if_table.h"
#include "output_filter.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "reference_freq.h"
#include <cmath>
#include <cstdint>
#include <cstdio>

void annotate_program() {
	bi_decl(bi_program_description("SPI ADC read & magic DSP"));
//	bi_decl(bi_4pins_with_names(
//		PICO_DEFAULT_SPI_SCK_PIN,
//		"SCK pin",
//		PICO_DEFAULT_SPI_TX_PIN,
//		"TX pin",
//		PICO_DEFAULT_SPI_RX_PIN,
//		"RX pin",
//		PICO_DEFAULT_SPI_CSN_PIN,
//		"CSN pin"
//	));
	bi_decl(bi_3pins_with_func(
		PICO_DEFAULT_SPI_TX_PIN,
		PICO_DEFAULT_SPI_RX_PIN,
		PICO_DEFAULT_SPI_SCK_PIN,
		GPIO_FUNC_SPI
	));
}

void adc_test() {
	// get ready for spi
	const size_t buffer_length = 17544; // XXX: for an integer # of cycles
	const size_t audio_extra = 77; // XXX: so that we don't underrun
	const size_t audio_length = buffer_length/4 + audio_extra;
	const size_t extra_hop = buffer_length/4 / audio_extra;

	const uint baud = 21e6; // 20.8 MHz spi clock ⇒ 1.0965 MHz sample rate
	adc_spi<buffer_length> adc(
		spi_default,
		baud,
		PICO_DEFAULT_SPI_TX_PIN,
		PICO_DEFAULT_SPI_RX_PIN,
		PICO_DEFAULT_SPI_SCK_PIN
	);
	std::array<int8_t, buffer_length> mult_with_if;
	std::array<int8_t, buffer_length> filtered;
	std::array<uint32_t, audio_length + 33> audio_buffer_1;
	std::array<uint32_t, audio_length + 33> audio_buffer_2;

	const uint8_t half_voltage = static_cast<uint8_t>(3.3/2 * 0xff/3.3);
	const double sampling_rate = 1.0965e6; // in Hz

	// create an intermediate frequency reference at 455 kHz
	const if_lookup_table<int8_t, buffer_length> if_table(
		25.0, 455.0e3, sampling_rate
	);

	// set up the audio output jack
	const uint audio_pin = 22;
	audio_out a(audio_pin, sampling_rate/4);

	auto* current_buffer = &audio_buffer_1;
	bool buffer_1 = true;

	while (true) {
		a.play(current_buffer->data(), audio_length);
		adc.start();

		if (buffer_1) {
			current_buffer = &audio_buffer_2;
		} else {
			current_buffer = &audio_buffer_1;
		}
		buffer_1 = !buffer_1;

		// multiply by the IF frequency and filter
		size_t audio_i = 0;
		size_t hop_counter = 0;
		size_t total_hops = 0;
		for (size_t i = 0; i < buffer_length; ++i) {
			mult_with_if[i] = (adc[i] - 127); // *if_table[i] >> 4;
			auto next_out = 2*abs(mult_with_if[i]) + 90;
			if (i % 4 == 0) {
				(*current_buffer)[audio_i++] = next_out;
				if (hop_counter == extra_hop) {
					(*current_buffer)[audio_i++] = next_out;
					hop_counter = 0;
					++total_hops;
				}
				++hop_counter;
			}
		}
		if_filter(mult_with_if.data(), filtered.data(), buffer_length);

		// take a sum (because yeah)
		long int sum = 0;
		for (size_t i = 0; i < buffer_length; ++i) {
			sum += mult_with_if[i];
		}
		volatile long int dont_optimize = sum + 1;

		// see how much free time we have
		a.wait();
		auto start_of_free = get_absolute_time();
		adc.wait(true);
		int64_t free_time = absolute_time_diff_us(
			start_of_free, get_absolute_time()
		);

//		printf(
//			"\e[G\e[K"
//			"free time: %lld us"
//			"; hops: %zu"
//			"; index: %zu/%zu",
//			free_time, total_hops, audio_i, audio_length
//		);
	}
}

void pwm_test() {
	reference_freq::mostly_configure();
	reference_freq::set_mhz(14.000);

	float freq = 14.000;
	while (true) {
		freq += .01;
		if (freq > 14.350) freq = 14.000;

		reference_freq::set_mhz(freq);
		printf(
			"now running at %.3f (%.3f) MHz\n",
			freq, reference_freq::actual_freq(freq)
		);

		sleep_ms(10e3);
	}
}

void audio_test() {
	const double sampling_rate = 455e3; // in Hz
	const size_t buffer_length = 8273;

	// create a fifth around 110 Hz
	const if_lookup_table<uint32_t, buffer_length> root(
		60, 110, sampling_rate
	);

	const if_lookup_table<uint32_t, buffer_length> fifth(
		45, 110*3.0/2, sampling_rate
	);

	std::array<uint32_t, buffer_length> chord;
	for (size_t i = 0; i < buffer_length; ++i) {
		chord[i] = root[i] + fifth[i] + 60;
	}

	// set up the audio output jack
	const uint audio_pin = 22;
	audio_out a(audio_pin, sampling_rate);

	// play it
	while (true) {
		a.play(chord.data(), buffer_length);
		a.wait();
	}
}

int main() {
	annotate_program();
	stdio_init_all();

	adc_test();
//	pwm_test();
//	audio_test();

	for (;;) tight_loop_contents();
}

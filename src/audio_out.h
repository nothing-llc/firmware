/*
 * audio out over pwm via dma. yay!
 *
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#ifndef AUDIO_OUT_H
#define AUDIO_OUT_H

#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

class audio_out {
public:
	audio_out(uint pin, double sampling_freq);
	~audio_out();

	// play some audio asynchronously
	void play(const uint32_t* samples, size_t length);

	// 
	void wait();

private:
	struct {
		uint pin;
		uint slice;
		pwm_config config;
	} pwm;

	struct {
		uint channel;
		dma_channel_config config;
	} dma;
};

#endif

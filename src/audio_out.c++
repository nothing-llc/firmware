#include "audio_out.h"

#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "hardware/structs/pwm.h"
#include "pico/stdlib.h"

constexpr const static float clock_speed_mhz = 125; // XXX

audio_out::audio_out(uint pin, double sampling_freq) : pwm.pin{pin} {
	// set up for pwm output
	gpio_set_function(pin, GPIO_FUNC_PWM);
	pwm.slice = pwm_gpio_to_slice_num(pin);
	pwm.config = pwm_get_default_config();
	pwm_config_set_clkdiv(&pwm.config, clock_speed_mhz/sampling_freq);
	pwm_config_set_wrap(&pwm.config, 0xff); // 8-bit samples, soooo
	pwm_init(slice, &pwm.config, true);
	pwm_set_gpio_level(pin, 0);

	// set up for dma output
	dma.channel = dma_claim_unused_channel(true);
	dma.config = dma_channel_get_default_config(dma.channel);
	channel_config_set_transfer_data_size(&dma.config, DMA_SIZE_8);

	// set up to transfer data based on the pwm dreq
	channel_config_set_dreq(&dma.config, pwm_get_dreq(pwm.slice));
}

audio_out::~audio_out() {
	dma_channel_unclaim(dma.channel);
}

void audio_out::play(const uint8_t* samples, size_t length) {
	dma_channel_configure(
		dma.channel, &dma.config,
		&pwm_hw->slice[pwm.slice].cc, // XXX: write to counter compare
		samples, // read from samples,
		length,
		true // begin immediately
	);
}

void audio_out::wait() {
	dma_channel_wait_for_finish_blocking(dma.channel);
}

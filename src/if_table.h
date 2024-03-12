/*
 * creates a lookup table for our intermediate frequency. not done yet.
 *
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#ifndef IF_TABLE_H
#define IF_TABLE_H

#define _USE_MATH_DEFINES

#include <array>
#include <cmath>
#include <cstddef>

template<typename data_type, size_t buffer_length>
class if_lookup_table {
public:
	if_lookup_table(double scale, double freq, double sampling_rate);

	inline data_type& operator[] (size_t i) {
		return table[i];
	}

	const inline data_type& operator[] (size_t i) const {
		return table[i];
	}

private:
	std::array<data_type, buffer_length> table;
};

template<typename data_type, size_t buffer_length>
if_lookup_table<data_type, buffer_length>::if_lookup_table(
	double scale, double freq, double sampling_rate
) {
	const double digital_freq = 2*M_PI*freq/sampling_rate;

	for (size_t i = 0; i < buffer_length; ++i) {
		table[i] = static_cast<data_type>(
			scale*std::sin(digital_freq*i)
		);
	}
}

#endif

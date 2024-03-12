/*
 * interface to the output filter for IF demodulation. assumes an IF frequency
 * of 455 kHz and a sampling rate of 1.0965 MHz.
 *
 * copyright (c) 2024  thomas coor <thomas.coor@cooper.edu>
 * copyright (c) 2024  catherine van west <catherine.vanwest@cooper.edu>
 */

#ifndef OUTPUT_FILTER_H
#define OUTPUT_FILTER_H

#include <cstddef>
#include <cstdint>

/*
 * arguments:
 * - `in_buffer`: data to be filtered
 * - `out_buffer`: location for filtered data to be written
 * - `length`: elements in le buffers
 */
void if_filter(const int8_t* in_buffer, int8_t* out_buffer, size_t length);

#endif

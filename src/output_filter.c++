#include "output_filter.h"

void if_filter(const int8_t* in_buffer, int8_t* out_buffer, size_t length) {
	
	int8_t b[6] = {1.0000,   -2.8591,    1.8631,    1.8631,   -2.8591,    1.0000};
	int8_t a[6] = {1.0000,   -4.4992,    8.1200,   -7.3463,    3.3310,   -0.6054};
	int8_t v[length+6];	// there is a buffer of length 6 to accomodate the n-m's in the realization
	// int8_t y[length+6];	// initialize output array
	for (int n = 0; n < length; n++) 
	{
		v[n+6] = in_buffer[n] - a[0]*v[n+6-1] - a[1]*v[n+6-2] - a[2]*v[n+6-3] - a[3]*v[n+6-4] - a[4]*v[n+6-5] - a[5]*v[n+6-6];
		y[n+6] = in_buffer[n] - b[0]*v[n+6-1] - b[1]*v[n+6-2] - b[2]*v[n+6-3] - b[3]*v[n+6-4] - b[4]*v[n+6-5] - b[5]*v[n+6-6];
	}
	out_buffer = y;

}

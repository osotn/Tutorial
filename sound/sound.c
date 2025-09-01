/* gcc -W -Wall -O2 $(shell pkg-config --cflags libpulse-simple) -o sine sine.c -lm $(shell pkg-config --libs libpulse-simple) */

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include <pulse/simple.h>

#define FREQ_MIN 100
#define FREQ 400
#define RATE 44100

static int16_t samples[RATE / FREQ_MIN];

static const pa_sample_spec spec = {
	.format		= PA_SAMPLE_S16NE,
	.rate		= RATE,
	.channels	= 1,
};

int main(int argn, char* argv[])
{
	double x = 0;
	int freq = FREQ;

	if (argn == 2)
		freq = atoi(argv[1]);

	for (int i = 0; i < RATE / freq; i++, x += (2 * M_PI * freq) / RATE)
		samples[i] = INT16_MAX * sin(x);

	pa_simple *s = pa_simple_new(NULL, "sine", PA_STREAM_PLAYBACK, NULL, "sine", &spec, NULL, NULL, NULL);
	if (!s) 
		return EXIT_FAILURE;

	for (int i = 0; i < freq; i++)	
		pa_simple_write(s, samples, RATE / freq, NULL);

	pa_simple_drain(s, NULL);
	pa_simple_free(s);

	return EXIT_SUCCESS;
}


#include "stp_synthetic_reverb.h"
#include <math.h>

stp_synthetic_reverb *stp_synthetic_reverb_new()
{
    stp_synthetic_reverb *x = (stp_synthetic_reverb *)malloc(sizeof(stp_synthetic_reverb));

    // initialize and set delay of comb filter objects according to pre-calculated values in stp_defines
    float comb_delay[NUM_COMB] = {COMB1_DELAY, COMB2_DELAY, COMB3_DELAY, COMB4_DELAY, COMB5_DELAY, COMB6_DELAY, COMB7_DELAY, COMB8_DELAY};

    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
        x->comb[i] = stp_comb_filter_new(BUFFER_SIZE);
        stp_comb_filter_set_delay(x->comb[i], comb_delay[i]);
    }

    // initialize, set gain and delay of allpass filter objects according to pre-calculated values in stp_defines
    float ap_delay[NUM_AP] = {AP_1_DELAY, AP_2_DELAY, AP_3_DELAY, AP_4_DELAY};

    for (unsigned int i = 0; i < NUM_AP; i++)
    {
        x->ap[i] = stp_all_pass_filter_new(BUFFER_SIZE);
        stp_all_pass_filter_set_gain(x->ap[i], AP_GAIN);
        stp_all_pass_filter_set_delay(x->ap[i], ap_delay[i]);
    }

    return (void *)x;
}

void stp_synthetic_reverb_free(stp_synthetic_reverb *x)
{
    // free buffers and objects
    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
        free(x-> comb_buffer[i]);
        stp_comb_filter_free(x->comb[i]);
    }

    for (unsigned int i = 0; i < NUM_AP; i++)
    {
        free(x-> ap_buffer[i]);
        stp_all_pass_filter_free(x->ap[i]);
    }

    free(x-> comb_sum_buffer);
    free(x);
}

void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size)
{
    // split input into the parallel comb filters
    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
    	 stp_comb_filter_perform(x->comb[i], in, x->comb_buffer[i], vector_size);
    }
    // sum the outputs of the comb filters..
    stp_synthetic_reverb_comb_filter_sum_up(x, vector_size);

    // ..and use the result to feed the series of allpass filters
    stp_all_pass_filter_perform(x->ap[0], x->comb_sum_buffer, x->ap_buffer[0], vector_size);

    for (unsigned int i = 1; i < NUM_AP; i++)
    {
    	stp_all_pass_filter_perform(x->ap[i], x-> ap_buffer[i-1], x->ap_buffer[i], vector_size);
    }

    // scale the output to avoid clipping
    for (unsigned int i = 0; i < vector_size; i++)
    {
    	out[i] = x->ap_buffer[NUM_AP-1][i] / (float)OUTPUT_SCALE;
    }
}

void stp_synthetic_reverb_comb_filter_sum_up(stp_synthetic_reverb *x, unsigned int vector_size)
{
	for (unsigned int i = 0; i < vector_size; i++)
	{
		float sum = .0;
		for (unsigned int j = 0; j < NUM_COMB; j++)
		{
			sum += x->comb_buffer[j][i];
		}
		x->comb_sum_buffer[i] = sum;
	}
}

void stp_synthetic_reverb_set_room_size(stp_synthetic_reverb *x, float _room_size)
{
    // feedback scale according to empirical testing 0.7 - 0.98 -> span is 0.28
    // feedback input between 0 and 1!
    _room_size = 0.7 + (0.28 * _room_size);

    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
    	stp_comb_filter_set_feedback(x->comb[i], _room_size);
    }
}

void stp_synthetic_reverb_set_damping(stp_synthetic_reverb *x, float _damping)
{
    // damping scale according to empirical testing between 0 and 0.4
    _damping = 0.4 * _damping;

    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
    	stp_comb_filter_set_cutoff(x->comb[i], _damping);
    }
}

void stp_synthetic_reverb_allocate_temp_buffer(stp_synthetic_reverb *x, unsigned int vector_size)
{
    // allocate memory for buffers and down pass temp buffer size to lower level modules
    for (unsigned int i = 0; i < NUM_COMB; i++)
    {
        x->comb_buffer[i] = (float *)calloc(vector_size, sizeof(float));
        stp_comb_filter_allocate_temp_buffer(x->comb[i], vector_size);
    }

    for (unsigned int i = 0; i < NUM_AP; i++)
    {
        x->ap_buffer[i] = (float *)calloc(vector_size, sizeof(float));
        stp_all_pass_filter_allocate_temp_buffer(x->ap[i], vector_size);
    }

    x->comb_sum_buffer = (float *)calloc(vector_size, sizeof(float));
}

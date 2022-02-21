//
//  stp_all_pass_filter.c
//  stp_synthetic_reverb~
//
//

#include "stp_all_pass_filter.h"

stp_all_pass_filter *stp_all_pass_filter_new(long _buffer_size)
{
    stp_all_pass_filter *x = (stp_all_pass_filter *)malloc(sizeof(stp_all_pass_filter));
    x->gain = .0;
    x->delay_line1 = stp_delay_new(_buffer_size);
    x->delay_line2 = stp_delay_new(_buffer_size);

    return (void *)x;
}

void stp_all_pass_filter_free(stp_all_pass_filter *x)
{
    free(x->delay_line_out1);
    free(x->delay_line_out2);
    stp_delay_free(x->delay_line1);
    stp_delay_free(x->delay_line2);
    free(x);
}

void stp_all_pass_filter_perform(stp_all_pass_filter *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size)
{
    for (unsigned int i = 0; i < vector_size; i++)
    {
    	out[i] = ((1 + x->gain) * (x->delay_line_out1[i])) - in[i] + x->delay_line_out2[i] * x->gain;
    }

    stp_delay_perform(x->delay_line1, in, x->delay_line_out1, vector_size);
    stp_delay_perform(x->delay_line2, out, x->delay_line_out2, vector_size);
}

void stp_all_pass_filter_set_delay(stp_all_pass_filter *x, float _delay_in_samples)
{
    stp_delay_set_delay(x->delay_line1, _delay_in_samples);
    stp_delay_set_delay(x->delay_line2, _delay_in_samples);
}

void stp_all_pass_filter_set_gain(stp_all_pass_filter *x, float _gain)
{
    if (_gain >= 1)
    	_gain = 1;
    else if (_gain <= 0)
    	_gain = 0;

    x->gain = _gain;
}

void stp_all_pass_filter_allocate_temp_buffer(stp_all_pass_filter *x, unsigned int vector_size)
{
    x->delay_line_out1 = (float *)calloc(vector_size, sizeof(float));
    x->delay_line_out2 = (float *)calloc(vector_size, sizeof(float));
}

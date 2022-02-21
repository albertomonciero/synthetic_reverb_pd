#include "stp_comb_filter.h"

stp_comb_filter *stp_comb_filter_new(long _buffer_size)
{
    stp_comb_filter *x = (stp_comb_filter *)malloc(sizeof(stp_comb_filter));
    x->feedback = .0;
    x->lowpass = stp_low_pass_new();
    x->delay_line = stp_delay_new(_buffer_size);

    return (stp_comb_filter *)x;
}

void stp_comb_filter_free(stp_comb_filter *x)
{
    free(x->delay_out);
    free(x->lowpass_out);
    stp_low_pass_free(x->lowpass);
    stp_delay_free(x->delay_line);
    free(x);
}

void stp_comb_filter_set_feedback(stp_comb_filter *x, float _feedback)
{
    if (_feedback >= 0.99)
    	_feedback = 0.99;
    else if (_feedback <= 0)
    	_feedback = 0;

    x->feedback = _feedback;
}

void stp_comb_filter_set_delay(stp_comb_filter *x, float _delay)
{
    stp_delay_set_delay(x->delay_line, _delay);
}

void stp_comb_filter_set_cutoff (stp_comb_filter *x, float _cutoff)
{
    stp_low_pass_set_cutoff(x->lowpass, _cutoff);
}

void stp_comb_filter_perform(stp_comb_filter *x, float *in, float *out, unsigned int vector_size)
{
    for (unsigned int i = 0; i < vector_size; i++)
    {
    	out[i] = in[i] + x->feedback * x->lowpass_out[i];
    }

    stp_delay_perform(x->delay_line, out, x->delay_out, vector_size);
    stp_low_pass_perform(x->lowpass, x->delay_out, x->lowpass_out, vector_size);
}

void stp_comb_filter_allocate_temp_buffer(stp_comb_filter *x, unsigned int vector_size)
{
    x->delay_out = (float *)calloc(vector_size, sizeof(float));
    x->lowpass_out = (float *)calloc(vector_size, sizeof(float));
}

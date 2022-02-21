#include "stp_low_pass.h"

stp_low_pass *stp_low_pass_new()
{
    stp_low_pass *x = (stp_low_pass *)malloc(sizeof(stp_low_pass));
    x->cutoff = 0;
    x->last_sample = 0;

    return (stp_low_pass *)x;
}

void stp_low_pass_free(stp_low_pass *x)
{
    free(x);
}

void stp_low_pass_set_cutoff(stp_low_pass *x, float _cutoff)
{
    if (_cutoff >= 1)
    	_cutoff = 1;
    else if (_cutoff <= 0)
    	_cutoff = 0;

    x->cutoff = _cutoff;
}

void stp_low_pass_perform(stp_low_pass *x, float *in, float *out, unsigned int vector_size)
{
    for (unsigned int i = 0; i < vector_size; i++)
    {
        out[i] = (1 - x->cutoff) * in[i] + x-> cutoff * x->last_sample;
        x->last_sample = out[i];
    }
}

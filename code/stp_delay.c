#include "stp_delay.h"

stp_delay *stp_delay_new(long _buffer_size)
{
    stp_delay *x = (stp_delay *)malloc(sizeof(stp_delay));
    x->buffer_size = _buffer_size;
    x->buffer = (long *)calloc(x->buffer_size + 1, sizeof(long));
    x->circular_pointer = x->buffer;
    x->delay_sample = .0;
    x->delay_in_samples = .0;

    return x;
}

void stp_delay_free(stp_delay *x)
{
    free(x->buffer);
    free(x);
}

void stp_delay_perform(stp_delay *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size)
{
    for (unsigned int i = 0; i < vector_size; i++)
    {
        *(x->circular_pointer) = in[i];
        x-> delay_sample = stp_delay_interpolate_tap_into_buffer(x->buffer_size, x->delay_in_samples, x->buffer, x->circular_pointer);
        out[i] = (x-> delay_sample);
        stp_delay_decrement_circular_pointer(x->buffer_size, x->buffer, &(x->circular_pointer));
    }
}

void stp_delay_set_delay(stp_delay *x, float _delay_in_samples)
{
    if (_delay_in_samples < 0 || _delay_in_samples >= ((x-> buffer_size) - 1))
        _delay_in_samples = 0;

    x->delay_in_samples = _delay_in_samples ;
}

float stp_delay_tap_into_buffer(long buffer_size, float *buffer_pointer, float *circular_pointer, unsigned int index)
{
    return buffer_pointer[(circular_pointer - buffer_pointer + index) % ((buffer_size) + 1)];
}

float stp_delay_interpolate_tap_into_buffer(long buffer_size, float delay_in_samples, float *buffer_pointer, float *circular_pointer)
{
    // positions in buffer to interpolate between
    unsigned int i, j;
    float si, sj;

    // interpolate between si and sj
    i = floor(delay_in_samples);
    // if i=D, then j=0 otherwise, j=i+1
    j = (i + 1) % ((buffer_size) + 1);

    // get buffer values by taping into buffer without interpolation
    // si(n) = x(n-i)
    si = stp_delay_tap_into_buffer(buffer_size, buffer_pointer, circular_pointer, i);
    // sj(n) = x(n-j)
    sj = stp_delay_tap_into_buffer(buffer_size, buffer_pointer, circular_pointer, j);

    return si + ((delay_in_samples) - i) * (sj - si);
}

void stp_delay_wrap_circular_pointer_to_start(long buffer_size, float *buffer_pointer, float **circular_pointer)
{
    // when *circular_pointer=buffer_pointer+buffer_size+1, it wraps around to *circular_pointer=buffer_pointer
    if (*circular_pointer > buffer_pointer + buffer_size)
        *circular_pointer -= buffer_size + 1;
    // when *circular_pointer=buffer_pointer-1, it wraps around to *circular_pointer=buffer_pointer+buffer_size
    else if (*circular_pointer < buffer_pointer)
        *circular_pointer += buffer_size + 1;
}

void stp_delay_decrement_circular_pointer(long buffer_size, float *buffer_pointer, float **circular_pointer)
{
    // decrement pointer and wrap modulo-buffer_size+1
    (*circular_pointer)--;
    // when *circular_pointer=buffer_pointer-1, it wraps around to *circular_pointer=buffer_pointer+buffer_size
    stp_delay_wrap_circular_pointer_to_start(buffer_size, buffer_pointer, circular_pointer);
}

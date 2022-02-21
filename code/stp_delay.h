/**
 * @file stp_delay.h
 * @author A.Monciero, C.Jaedicke <br>
 * An interpolated delay <br>
 * <br>
 * @brief Audio Object for adding delay to the input<br>
 * <br>
 * stp_delay allows for delaying<br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_delay_h
#define stp_delay_h

#define STP_INPUTVECTOR_USE_FLOAT
#define STP_OUTPUTVECTOR_USE_FLOAT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

/**
 * @struct stp_delay
 * @brief A structure for a delay object <br>
 * @var stp_delay::buffer The buffer we save the incoming signal in <br>
 * @var stp_delay::delay_in_samples The parameter value for adjusting the <br>
 * delay of the incoming signal
 * @var stp_delay::buffer_size The size of the delay buffer <br>
 * @var stp_delay::circular_pointer Circular pointer to the delay buffer <br>
 * @var stp_delay::delay_sample The current sample from the delay buffer <br>
 */
typedef struct stp_delay
{
    float *buffer;              /**< Delay in buffer */
    float delay_in_samples;     /**< Delay in samples */
    long buffer_size;           /**< Size of the delay buffer */
    float *circular_pointer;    /**< Circular pointer to delay buffer */
    float delay_sample;         /**< The current sample from the delay buffer */
} stp_delay; /**< A structure for a delay line object*/

/**
 * @related stp_delay
 * @brief Creates a new delay object<br>
 * The function sets the buffer size and delay parameter of <br>
 * the delay class
 * @return a pointer to the newly created stp_delay object <br>
 */
stp_delay *stp_delay_new(long _buffer_size);

/**
 * @related stp_delay
 * @brief Frees a delay object<br>
 * @param x My delay object <br>
 * The function frees the allocated memory<br>
 * of a delay object
 */
void stp_delay_free(stp_delay *x);

/**
 * @related stp_delay
 * @brief Performs the delay in realtime. <br>
 * @param x My delay object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function stp_delay_perform delays any <br>
 * incoming signal and copies the result to the output vector <br>
 */
void stp_delay_perform(stp_delay *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size);

/**
 * @related stp_delay
 * @brief Sets the delay time in samples with floating point precision. <br>
 * @param x My delay object <br>
 * @param _delay_in_samples The delay in samples <br>
 * Sets the delay time in samples with floating point precision. <br>
 * Delays exceeding the buffer size are handeled by setting the delay to zero. <br>
 */
void stp_delay_set_delay(stp_delay *x, float _delay_in_samples);

/**
 * @related stp_delay
 * @brief Non-interpolating retrieval of samples in the delay buffer. <br>
 * @param buffer_size Size of the total delay buffer <br>
 * @param buffer_pointer Pointer to the delay buffer <br>
 * @param circular_pointer Circular pointer iterating through the buffer <br>
 * @param index Index of the sample we want to tap in <br>
 * Non-interpolating retrieval of samples in the delay buffer. <br>
 * @return A sample from the delay buffer. <br>
 */
float stp_delay_tap_into_buffer(long buffer_size, float *buffer_pointer, float *circular_pointer, unsigned int index);

/**
 * @related stp_delay
 * @brief Interpolating retrieval of samples in the delay buffer. <br>
 * @param buffer_size Size of the total delay buffer <br>
 * @param delay_in_samples Desired non-integer delay <br>
 * @param buffer_pointer Pointer to the delay buffer <br>
 * @param circular_pointer Circular pointer iterating through the buffer <br>
 * @param index Index of the sample we want to tap in <br>
 * Interpolating retrieval of samples in the delay buffer. <br>
 * Delays exceeding the buffer size are handeled by setting the delay to zero. <br>
 * @return A interpolated sample from the delay buffer. <br>
 */
float stp_delay_interpolate_tap_into_buffer(long buffer_size, float delay_in_samples, float *buffer_pointer, float *circular_pointer);

/**
 * @related stp_delay
 * @brief Resets the circular pointer. <br>
 * @param buffer_size Size of the total delay buffer <br>
 * @param buffer_pointer Pointer to the delay buffer <br>
 * @param circular_pointer Circular pointer iterating through the buffer <br>
 * Resets the circular pointer to the start or end of the delay buffer. <br>
 */
void stp_delay_wrap_circular_pointer_to_start(long buffer_size, float *buffer_pointer, float **circular_pointer);

/**
 * @related stp_delay
 * @brief Decrements the circular pointer. <br>
 * @param buffer_size Size of the total delay buffer <br>
 * @param buffer_pointer Pointer to the delay buffer <br>
 * @param circular_pointer Circular pointer iterating through the buffer <br>
 * Decrements the circular pointer and calls the wrap function. <br>
 */
void stp_delay_decrement_circular_pointer(long buffer_size, float *buffer_pointer, float **circular_pointer);

#endif /* stp_delay_h */

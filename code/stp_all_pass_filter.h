/**
 * @file stp_all_pass_filter.h
 * @author A.Monciero, C.Jaedicke <br>
 * An allpass filter <br>
 * <br>
 * @brief Audio Object for adding allpass filter to the input <br>
 * <br>
 * stp_all_pass_filter allows for allpass filtering <br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_all_pass_filter_h
#define stp_all_pass_filter_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "stp_delay.h"

/**
 * @struct stp_all_pass_filter
 * @brief A structure for a allpass object <br>
 * @var stp_all_pass_filter::delay_line1 First allpass filter delay line <br>
 * @var stp_all_pass_filter::delay_line2 Second allpass filter delay line <br>
 * @var stp_all_pass_filter::delay_line_out1 The buffer we save the first delay line output in <br>
 * @var stp_all_pass_filter::delay_line_out2 The buffer we save the second delay line output in <br>
 * @var stp_all_pass_filter::gain Adjustable gain value <br>
 */

typedef struct stp_all_pass_filter
{
    stp_delay *delay_line1;   /**< First allpass filter delay line */
    stp_delay *delay_line2;   /**< Second allpass filter delay line */
    float *delay_line_out1;   /**< First allpass filter output*/
    float *delay_line_out2;   /**< Second allpass filter output*/
    float gain;               /**< Allpass filter gain*/
} stp_all_pass_filter;  /**< A structure for a allpass object*/

/**
 * @related stp_all_pass_filter
 * @brief Creates a new allpass filter object<br>
 * The function sets the initial values for the allpass filter <br>
 * @return a pointer to the newly created stp_all_pass_filter object <br>
 */

stp_all_pass_filter *stp_all_pass_filter_new(long buffer_size);

/**
 * @related stp_all_pass_filter
 * @brief Frees a allpass filter object<br>
 * @param x My allpass filter object <br>
 * The function frees the allocated memory<br>
 * of a allpass filter object
 */
void stp_all_pass_filter_free(stp_all_pass_filter *x);

/**
 * @related stp_all_pass_filter
 * @brief Performs the allpass filter in realtime. <br>
 * @param x My allpass filter object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function stp_allpass_filter_perform processes the <br>
 * incoming signal with a allpass filter and copies the result to the output vector <br>
 */
void stp_all_pass_filter_perform(stp_all_pass_filter *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size);

/**
 * @related stp_all_pass_filter
 * @brief Sets the delay time in samples with floating point precision. <br>
 * @param x My allpass filter object <br>
 * @param _delay_in_samples The delay in samples <br>
 * Sets the delay time in samples with floating point precision. <br>
 * Calls the stp_delay set delay function. <br>
 */
void stp_all_pass_filter_set_delay(stp_all_pass_filter *x, float _delay_in_samples);

/**
 * @related stp_all_pass_filter
 * @brief Sets the gain value. <br>
 * @param x My allpass filter object <br>
 * @param _gain The gain <br>
 * Sets the gain value with floating point precision. <br>
 * Gain values exceeding 0 < gain < 1 are handelt by setting them to 0 or 1. <br>
 */
void stp_all_pass_filter_set_gain(stp_all_pass_filter *x, float _gain);

/**
 * @related stp_all_pass_filter
 * @brief Allocates temporary buffers to save output of other classes. <br>
 * @param x My allpass filter object <br>
 * @param vector_size The size of the i/o vectors <br>
 * Allocates temporary buffers to save output of other classes. <br>
 * Buffers for delay line output. <br>
 */
void stp_all_pass_filter_allocate_temp_buffer(stp_all_pass_filter *x, unsigned int vector_size);

#endif /* stp_all_pass_filter_h */

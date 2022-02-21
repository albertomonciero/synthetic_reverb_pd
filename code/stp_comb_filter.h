/**
 * @file stp_delay.h
 * @author A.Monciero, C.Jaedicke  <br>
 * An interpolated delay <br>
 * <br>
 * @brief Audio Object for adding delay to the input<br>
 * <br>
 * stp_delay allows for delaying<br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef COMB_FILTER_H_
#define COMB_FILTER_H_

#include "stp_delay.h"
#include "stp_low_pass.h"

/**
 * @struct stp_comb_filter
 * @brief A structure for a comb filter object <br>
 * @var stp::delay_line Comb filter delay line <br>
 * @var stp::lowpass Lowpass filter <br>
 * @var stp::feedback Adjustable feedback value <br>
 * @var stp::delay_out The buffer we save the delay line output in <br>
 * @var stp::lowpass_out The buffer we save the lowpass output in <br>
 */
typedef struct stp_comb_filter
{
    stp_delay *delay_line;    /**< Comb filter delay line */
    stp_low_pass *lowpass;    /**< Lowpass filter for the feedback path */
    float feedback;           /**< Current sample from the feedback path */
    float *delay_out;         /**< Delay line temporary output buffer */
    float *lowpass_out;       /**< Lowpass filter temporary output buffer */
} stp_comb_filter; /**< A structure for a feedback lowpass comb filter object*/

/**
 * @related stp_comb_filter
 * @brief Creates a new comb filter object<br>
 * The function sets the standard values for the comb filter. With delay buffer size = 44.1k <br>
 * @return a pointer to the newly created stp_comb_filter object <br>
 */
stp_comb_filter *stp_comb_filter_new(long _buffer_size);

/**
 * @related stp_comb_filter
 * @brief Frees a comb filter object<br>
 * @param x My comb filter object <br>
 * The function frees the allocated memory<br>
 * of a comb filter object
 */
void stp_comb_filter_free(stp_comb_filter *x);

/**
 * @related stp_comb_filter
 * @brief Sets the feedback value. <br>
 * @param x My comb filter object <br>
 * @param _feedback The feedback <br>
 * Sets the feedback value with floating point precision. <br>
 * Feedback values exceeding 0 < feedback < 1 are handelt by setting them to 0 or 0.99. <br>
 */
void stp_comb_filter_set_feedback(stp_comb_filter *x, float _feedback);

/**
 * @related stp_comb_filter
 * @brief Sets the delay time in samples with floating point precision. <br>
 * @param x My comb filter object <br>
 * @param _delay The delay in samples <br>
 * Sets the delay time in samples with floating point precision. <br>
 * Calls the stp_delay set delay function. <br>
 */
void stp_comb_filter_set_delay(stp_comb_filter *x, float _delay);

/**
 * @related stp_comb_filter
 * @brief Sets the cut off frequency value. <br>
 * @param x My comb filter object <br>
 * @param _cutoff The cut off frequency <br>
 * Sets the cut off frequency value with floating point precision. <br>
 * Calls the stp_lowpass set cut off frequency function. <br>
 */
void stp_comb_filter_set_cutoff (stp_comb_filter *x, float _cutoff);

/**
 * @related stp_comb_filter
 * @brief Performs the comb filter in realtime. <br>
 * @param x My comb filter object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function stp_comb_filter_perform processes the <br>
 * incoming signal with a comb filter and copies the result to the output vector <br>
 */
void stp_comb_filter_perform(stp_comb_filter *x, float *in, float *out, unsigned int vector_size);

/**
 * @related stp_comb_filter
 * @brief Allocates temporary buffers to save output of other classes. <br>
 * @param x My comb filter object <br>
 * @param vector_size The size of the i/o vectors <br>
 * Allocates temporary buffers to save output of other classes. <br>
 * Buffers for lowpass and delay line output. <br>
 */
void stp_comb_filter_allocate_temp_buffer(stp_comb_filter *x, unsigned int vector_size);

#endif /* COMB_FILTER_H_ */

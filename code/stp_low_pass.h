/**
 * @file stp_low_pass.h
 * @author A.Monciero, C.Jaedicke <br>
 * A single pole lowpass filter class <br>
 * <br>
 * @brief Audio Object for lowpass filtering the input <br>
 * <br>
 * stp_low_pass allows for lowpass filtering <br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_low_pass_h
#define stp_low_pass_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

/**
 * @struct stp_low_pass
 * @brief A structure for a lowpass filter object <br>
 * @var stp::cutoff The cut off frequency of the filter <br>
 * @var stp::last_sample Saves the last output sample for the recursive structure <br>
 */
typedef struct stp_low_pass
{
    float cutoff;         /**< Lowpass filter cutoff frequency*/
    float last_sample;    /**< Last sample for the one-pole filter structure*/
} stp_low_pass; /**< A structure for a lowpass filter object*/

/**
 * @related stp_low_pass
 * @brief Creates a new lowpass object<br>
 * The function sets the default parameter of <br>
 * the lowpass class
 * @return a pointer to the newly created stp_low_pass object <br>
 */
stp_low_pass *stp_low_pass_new();

/**
 * @related stp_low_pass
 * @brief Frees a lowpass object<br>
 * @param x My lowpass object <br>
 * The function frees the allocated memory<br>
 * of a lowpass object
 */
void stp_low_pass_free(stp_low_pass *x);

/**
 * @related stp_low_pass
 * @brief Sets the cut off frequency value. <br>
 * @param x My lowpass object <br>
 * @param _cutoff The cut off frequency <br>
 * Sets the cut off frequency value with floating point precision. <br>
 * Values exceeding 0 <= cut-off <= 1 are set to 0 or 1 accordingly <br>
 */
void stp_low_pass_set_cutoff(stp_low_pass *x, float _delay_in_samples);

/**
 * @related stp_low_pass
 * @brief Performs the lowpass filter in realtime. <br>
 * @param x My lowpass filter object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function stp_low_pass_perform filters any incoming signal <br>
 * with a single pole lowpass filter and copies the result to the output vector <br>
 */
void stp_low_pass_perform(stp_low_pass *x, float *in, float *out, unsigned int vector_size);

#endif /* stp_low_pass_h */

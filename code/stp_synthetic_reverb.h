/**
 * @file stp_synthetic_reverb.h
 * @author A.Monciero, C.Jaedicke <br>
 * A synthetic reverb object <br>
 * <br>
 * @brief A synthetic reverb object for adding adjustable reverb to a signal <br>
 * <br>
 * stp_synthetic_reverb allows for adding adjustable reverb to <br>
 * any incoming audio signal. For more information please refer to the <a href = "http://www.aes.org/e-lib/browse.cfm?elib=18307" > AES Paper on AmbiFreeVerb 2 </a> <br>
 * <br>
 */

#ifndef stp_synthetic_reverb_h
#define stp_synthetic_reverb_h

#define STP_INPUTVECTOR_USE_FLOAT
#define STP_OUTPUTVECTOR_USE_FLOAT

#include <stdio.h>
#include <stdlib.h>
#include "stp_defines.h"
#include "stp_comb_filter.h"
#include "stp_all_pass_filter.h"

/**
 * @struct stp_synthetic_reverb
 * @brief A structure for a synthetic reverb object <br>
 * @var stp_synthetic_reverb::comb Array of comb filter objects <br>
 * @var stp_synthetic_reverb::ap Array of allpass filter objects <br>
 * @var stp_synthetic_reverb::comb_buffer Array of buffer for comb filter outputs <br>
 * @var stp_synthetic_reverb::ap_buffer Array of buffer for allpass filter output <br>
 * @var stp_synthetic_reverb::comb_sum_buffer Buffer for summing up all comb filter buffers <br>
 */
typedef struct stp_synthetic_reverb
{
    stp_comb_filter *comb[NUM_COMB];  /**< Array of comb filters objects*/
    float *comb_buffer[NUM_COMB];     /**< Array of buffer for the comb filters outputs*/
    stp_all_pass_filter *ap[NUM_AP];  /**< Array of allpass filters objects*/
    float *ap_buffer[NUM_AP];         /**< Array of buffer for the allpass filters outputs*/
    float *comb_sum_buffer;           /**< Buffer for summing up all comb filter buffers*/
} stp_synthetic_reverb; /**< A structure for a schroder reverberator object*/

/**
 * @related stp_synthetic_reverb
 * @brief Creates a new synthetic reverb object<br>
 * The function sets the default parameters. <br>
 * @return a pointer to the newly created stp_synthetic_reverb object <br>
 */
stp_synthetic_reverb *stp_synthetic_reverb_new();

/**
 * @related stp_synthetic_reverb
 * @brief Frees a synthetic reverb object<br>
 * @param x My synthetic reverb object <br>
 * The function frees the allocated memory<br>
 * of a synthetic reverb object
 */
void stp_synthetic_reverb_free(stp_synthetic_reverb *x);

/**
 * @related stp_synthetic_reverb
 * @brief Performs the synthetic reverb in realtime. <br>
 * @param x My synthetic reverb object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function stp_synthetic_reverb adds adjustable reverb to any <br>
 * incoming signal and copies the result to the output vector <br>
 */
void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, unsigned int vector_size);

/**
 * @related stp_synthetic_reverb
 * @brief Sums up all comb filter outputs. <br>
 * @param x My stp_synthetic_reverb object <br>
 * @param vector_size The size of the i/o vectors <br>
 */
void stp_synthetic_reverb_comb_filter_sum_up(stp_synthetic_reverb *x, unsigned int vector_size);

/**
 * @related stp_synthetic_reverb
 * @brief Allocates all temporary output buffers. <br>
 * @param x My stp_synthetic_reverb object <br>
 * @param vector_size The size of the i/o vectors <br>
 */
void stp_synthetic_reverb_allocate_temp_buffer(stp_synthetic_reverb *x, unsigned int vector_size);

/**
 * @related stp_synthetic_reverb
 * @brief Sets the room_size value. <br>
 * @param x My stp_synthetic_reverb object <br>
 * @param feedback The room_size value <br>
 * Sets the room_size value with floating point precision <br>
 * Calls the set method from stp_comb_filters <br>
 */
void stp_synthetic_reverb_set_room_size(stp_synthetic_reverb *x, float _room_size);

/**
 * @related stp_synthetic_reverb
 * @brief Sets the _damping value. <br>
 * @param x My stp_synthetic_reverb object <br>
 * @param _damping The _damping value <br>
 * Sets the _damping value with floating point precision <br>
 * Calls the set method from stp_comb_filters <br>
 */
void stp_synthetic_reverb_set_damping(stp_synthetic_reverb *x, float _damping);

#endif /* stp_synthetic_reverb_h */

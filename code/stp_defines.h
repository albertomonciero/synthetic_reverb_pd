/**
 * @file stp_defines.h
 * @author A.Monciero, C.Jaedicke <br>
 * Definitions <br>
 * <br>
 * @brief Constant values used in the synthetic reverb plug-in <br>
 * <br>
 * Constant values used in the synthetic reverb plug-in <br>
 * <br>
 */

#ifndef stp_defines_h
#define stp_defines_h

#define NUM_COMB 8 /**< Number of comb filters. */
#define NUM_AP 4   /**< Number of allpass filters. */

/**
 * Delay constants for the comb filters.
 */
#define COMB1_DELAY 1116.171                     /**< Delay constant for the first comb filter */
#define COMB2_DELAY COMB1_DELAY + 71.83          /**< Delay constant for the second comb filter */
#define COMB3_DELAY COMB1_DELAY + 160.965        /**< Delay constant for the third comb filter */
#define COMB4_DELAY COMB1_DELAY + 239.904        /**< Delay constant for the fourth comb filter */
#define COMB5_DELAY COMB1_DELAY + 305.613        /**< Delay constant for the fifth comb filter */
#define COMB6_DELAY COMB1_DELAY + 374.85         /**< Delay constant for the sixth comb filter */
#define COMB7_DELAY COMB1_DELAY + 441            /**< Delay constant for the seventh comb filter */
#define COMB8_DELAY COMB1_DELAY + 500.976        /**< Delay constant for the eighth comb filter */

/**
 * Allpass gain value
 */
#define AP_GAIN 0.5


#define AP_1_DELAY 556.101  /**< Delay constant for the first allpass filter */
#define AP_2_DELAY 441      /**< Delay constant for the second allpass filter */
#define AP_3_DELAY 340.893  /**< Delay constant for the third allpass filter */
#define AP_4_DELAY 224.91   /**< Delay constant for the fourth allpass filter */

/**
 * Empirical scale factor to avoid clipping.
 */
#define OUTPUT_SCALE 40.0

/**
 * Buffer size for all filters based on the maximal delay time of the algorithm.
 */
#define BUFFER_SIZE (unsigned int)(2 * (COMB8_DELAY))

/**
 * Choose floating point or double precision for i/o vectors.
 */
#ifdef STP_INPUTVECTOR_USE_FLOAT
typedef float STP_INPUTVECTOR;
#else
typedef double STP_INPUTVECTOR;
#endif

/**
 * Choose floating point or double precision for i/o vectors.
 */
#ifdef STP_OUTPUTVECTOR_USE_FLOAT
typedef float STP_OUTPUTVECTOR;
#else
typedef double STP_OUTPUTVECTOR;
#endif

#endif /* stp_defines_h */

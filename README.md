# Synthetic Reverb External for Pure Data 

The Schroeder reverberator, consisting of eight parallel-connected feedback lowpass comb filters and a series connection of four allpass filters, is implemented as Pure Data external. For more information about the algorithm, please refer to the [AES Paper on AmbiFreeVerb 2](https://www.aes.org/e-lib/browse.cfm?elib=18307).

## Description
The algorithm implementation follows the Pure Data [externals guidelines](https://github.com/pure-data/externals-howto). Basically, to generate an external the following functions are required:  <br>
- *new()* to initialize a module instance
- *free()* to free the memory once an object is removed from the Pure Data environment
- *perform()* to process the audio signals
- *set()* to update the parameters used in the *perform()* routine <br>

A modular approach is adopted to separate the developed code from the Pure Data framework described in the guidelines, which generates the actual object used in the Pure Data environment. Moreover, a modular method is also applied to implement recurring functions in the two main algorithm components, the comb filter and the allpass filter. <br>
For example, a single comb filter requires a fractional delay line and a lowpass filter, which are implemented in *stp_delay.c* and
*stp_low_pass.c*, respectively. Instances of these modules are then utilized in *stp_comb_filter.c*. As an allpass filter is also built with delay lines, two stp_delay instances are used in *stp_all_pass_filter.c*. <br>
The whole algorithm is implemented in *stp_synthetic_reverb.c*, where the input signal is firstly splitted into the eight comb filters. The single output signals from the comb filters are summed and further processed through the series of four allpass filters to finally generate the output signal of the reverb. The single filters have a different set of fixed (gain, delay time) and variable (cutoff frequency, feedback amount) parameters. The used values and ranges were determined empirically. <br>
Using *stp_synthetic_reverb~.c*, the described algorithm is converted into a Pure Data object. <br>
The [documentation](https://github.com/albertomonciero/synthetic_reverb_pd/tree/main/docs) folder contains a detailed description of the used functions as HTML files generated with Doxygen.

## Usage
In the [external_linux](https://github.com/albertomonciero/synthetic_reverb_pd/tree/main/external_linux) folder a compiled version of the external is available. From there, 
```
puredata -lib stp_synthetic_reverb~ -open stp_synthetic_reverb_test.pd
```
to add the module to Pure Data and open a test patch. The module accepts two parameters, *room_size* and *damping*, in a range between 0-0.99 and 0-1.0, respectively. Parameter input values exceeding these limits are internally clipped.

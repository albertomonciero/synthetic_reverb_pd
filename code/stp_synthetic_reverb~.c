/**
 * @file stp_synthetic_reverb~.c
 * @author A.Monciero, C.Jaedicke <br>
 * A synthetic reverb object for pure data <br>
 * <br>
 * @brief A Pure Data synthetic reverb object for adding adjustable reverb to a signal <br>
 * <br>
 * stp_synthetic_reverb~ allows for adding adjustable reverb to <br>
 * any incoming audio signal. <br>
 * <br>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "m_pd.h"
#include "stp_delay.h"
#include "stp_synthetic_reverb.h"

static t_class *stp_synthetic_reverb_tilde_class;

/**
 * @struct stp_synthetic_reverb_tilde
 * @brief The Pure Data struct of the stp_synthetic_reverb_tilde~ object. <br>
 * @var stp_synthetic_reverb_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var stp_synthetic_reverb_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var stp_synthetic_reverb_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */
typedef struct stp_synthetic_reverb_tilde
{
    t_object  x_obj;
    t_sample f;
    stp_synthetic_reverb *synthetic_reverb;
    t_outlet *x_out;
} stp_synthetic_reverb_tilde;

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Calls the synthetic reverb perform method <br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the stp_synthetic_reverb_perform method. <br>
 * @return A pointer to the signal chain right behind the stp_delay_tilde object. <br>
 */
t_int *stp_synthetic_reverb_tilde_perform(t_int *w)
{
    stp_synthetic_reverb_tilde *x = (stp_synthetic_reverb_tilde *)(w[1]);
    t_sample *in = (t_sample *)(w[2]);
    t_sample *out = (t_sample *)(w[3]);
    int n = (int)(w[4]);

    stp_synthetic_reverb_perform(x->synthetic_reverb, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w + 5);
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Adds stp_synthetic_reverb_tilde_perform to the signal chain. <br>
 * @param x A pointer the stp_synthetic_reverb_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_synthetic_reverb_tilde_dsp(stp_synthetic_reverb_tilde *x, t_signal **sp)
{
    stp_synthetic_reverb_allocate_temp_buffer(x->synthetic_reverb, sp[0]->s_n);
    dsp_add(stp_synthetic_reverb_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the stp_synthetic_reverb_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_synthetic_reverb_tilde_free(stp_synthetic_reverb_tilde *x)
{
    stp_synthetic_reverb_free(x-> synthetic_reverb);
    outlet_free(x->x_out);
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Creates a new stp_synthetic_reverb_tilde object.<br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *stp_synthetic_reverb_tilde_new()
{
    stp_synthetic_reverb_tilde *x = (stp_synthetic_reverb_tilde *)pd_new(stp_synthetic_reverb_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x-> x_obj, &s_signal);
    x->synthetic_reverb = stp_synthetic_reverb_new();

    return (void *)x;
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Sets the room_size value. <br>
 * @param x My stp_synthetic_reverb_tilde object <br>
 * @param _room_size The room_size value <br>
 * Sets the room_size value with floating point precision <br>
 * Calls the set method from stp_synthetic_reverb <br>
 */
void stp_synthetic_reverb_tilde_set_room_size(stp_synthetic_reverb_tilde *x, float _room_size)
{
    if (_room_size)
        stp_synthetic_reverb_set_room_size(x->synthetic_reverb, _room_size);
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Sets the damping value. <br>
 * @param x My stp_synthetic_reverb_tilde object <br>
 * @param _damping The damping value <br>
 * Sets the damping value with floating point precision <br>
 * Calls the set method from stp_synthetic_reverb <br>
 */
void stp_synthetic_reverb_tilde_set_damping(stp_synthetic_reverb_tilde *x, float _damping)
{
    if (_damping)
        stp_synthetic_reverb_set_damping(x->synthetic_reverb, _damping);
}

/**
 * @related stp_synthetic_reverb_tilde
 * @brief Setup of stp_synthetic_reverb_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_synthetic_reverb_tilde_setup(void)
{
    stp_synthetic_reverb_tilde_class = class_new(gensym("stp_synthetic_reverb~"),
                                       (t_newmethod)stp_synthetic_reverb_tilde_new,
                                       (t_method)stp_synthetic_reverb_tilde_free,
                                       sizeof(stp_synthetic_reverb_tilde),
                                       CLASS_DEFAULT,
                                       A_DEFFLOAT, 0);

    class_addmethod(stp_synthetic_reverb_tilde_class, (t_method)stp_synthetic_reverb_tilde_dsp, gensym("dsp"), 0);
    class_addmethod(stp_synthetic_reverb_tilde_class, (t_method)stp_synthetic_reverb_tilde_set_room_size, gensym("room_size"), A_DEFFLOAT, 0);
    class_addmethod(stp_synthetic_reverb_tilde_class, (t_method)stp_synthetic_reverb_tilde_set_damping, gensym("damping"), A_DEFFLOAT, 0);

    CLASS_MAINSIGNALIN(stp_synthetic_reverb_tilde_class, stp_synthetic_reverb_tilde, f);
}

/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "calcPhaseDiff_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/math.h>
#include <volk/volk.h>

namespace gr {
namespace etreesModule {

using input_type = gr_complex;
using output_type = float;
calcPhaseDiff::sptr calcPhaseDiff::make()
{
    return gnuradio::make_block_sptr<calcPhaseDiff_impl>();
}


/*
 * The private constructor
 */
calcPhaseDiff_impl::calcPhaseDiff_impl()
    : gr::sync_block("calcPhaseDiff",
                     gr::io_signature::make(
                         2 /* min inputs */, 2 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
calcPhaseDiff_impl::~calcPhaseDiff_impl() {}

int calcPhaseDiff_impl::work(int noutput_items,
                             gr_vector_const_void_star& input_items,
                             gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto out = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    /*
    float in0_re, in0_im;
    float in1_re, in1_im;
    float mult0, mult1, mult2, mult3;
    float sub;
    float add;
    for (int index = 0; index < noutput_items; index++) {
        in0_re = in0[index].real();
        in0_im = in0[index].imag();
        in1_re = in1[index].real();
        in1_im = in1[index].imag();

        mult0 = in0_re * in1_im;
        mult1 = in1_re * in0_im;
        mult2 = in0_re * in1_re;
        mult3 = in0_im * in1_im;

	sub = mult0 - mult1;
	add = mult2 + mult3;
	out[index] = atan2f(sub, add);
    }
    */

    float *in0_re, *in0_im;
    float *in1_re, *in1_im;
    float *mult0, *mult1, *mult2, *mult3;
    float *sub;
    float *add;

    gr_complex *c;
    
    in0_re = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    in0_im = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    in1_re = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    in1_im = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());

    mult0 = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    mult1 = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    mult2 = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    mult3 = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());

    add = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());
    sub = (float *)volk_malloc(noutput_items * sizeof(float), volk_get_alignment());

    c = (gr_complex *)volk_malloc(noutput_items * sizeof(gr_complex), volk_get_alignment());

    volk_32fc_deinterleave_32f_x2(in0_re, in0_im, in0, noutput_items);
    volk_32fc_deinterleave_32f_x2(in1_re, in1_im, in1, noutput_items);

    volk_32f_x2_multiply_32f(mult0, in0_re, in1_im, noutput_items);
    volk_32f_x2_multiply_32f(mult1, in1_re, in0_im, noutput_items);
    volk_32f_x2_multiply_32f(mult2, in0_re, in1_re, noutput_items);
    volk_32f_x2_multiply_32f(mult3, in0_im, in1_im, noutput_items);

    volk_32f_x2_add_32f(add, mult2, mult3, noutput_items);
    volk_32f_x2_subtract_32f(sub, mult0, mult1, noutput_items);

    volk_32f_x2_interleave_32fc(c, add, sub, noutput_items);

    for (int index = 0; index < noutput_items; index++) {
        //    out[i] = std::arg (in[i]);                                                                                                    
        out[index] = gr::fast_atan2f(c[index]);
    }
    
    volk_free(in0_re);
    volk_free(in0_im);
    volk_free(in1_re);
    volk_free(in1_im);

    volk_free(mult0);
    volk_free(mult1);
    volk_free(mult2);
    volk_free(mult3);

    volk_free(add);
    volk_free(sub);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace etreesModule */
} /* namespace gr */

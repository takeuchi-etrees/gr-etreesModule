/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "calcPhaseDiff_impl.h"
#include <gnuradio/io_signature.h>

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
    float in0_re, in0_im;
    float in1_re, in1_im;
    float mult0, mult1, mult2, mult3;
    float sub;
    float add;
    for (int index = 0; index < noutput_items; index++) {
        in0_re = in0[0].real();
        in0_im = in0[0].imag();
        in1_re = in1[0].real();
        in1_im = in1[0].imag();

        mult0 = in0_re * in1_im;
        mult1 = in0_im * in0_im;
        mult2 = in0_re * in1_re;
        mult3 = in0_im * in0_im;

	sub = mult0 - mult1;
	add = mult2 - mult3;
        out[index] = atan(sub / add);
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace etreesModule */
} /* namespace gr */

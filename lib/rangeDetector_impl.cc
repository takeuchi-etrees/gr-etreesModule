/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "rangeDetector_impl.h"
#include <gnuradio/io_signature.h>
using namespace std;

namespace gr {
namespace etreesModule {

using input_type = float;
using output_type = float;
rangeDetector::sptr rangeDetector::make(float range)
{
    return gnuradio::make_block_sptr<rangeDetector_impl>(range);
}


/*
 * The private constructor
 */
rangeDetector_impl::rangeDetector_impl(float range)
    : gr::sync_block("rangeDetector",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _range = range;
    cur_val = 0.0;
    in_range = false;
    count = 0;
    time = 0;
    seq = 0;
}

/*
 * Our virtual destructor.
 */
rangeDetector_impl::~rangeDetector_impl() {}

int rangeDetector_impl::work(int noutput_items,
                             gr_vector_const_void_star& input_items,
                             gr_vector_void_star& output_items)
{
    uint64_t offset;
    pmt::pmt_t tag_key;
    pmt::pmt_t tag_value;
      
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

    auto ms_since_epoch(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());

    // Do <+signal processing+>
    for (int index = 0; index < noutput_items; index++) {
	if (in[index] < (cur_val - _range)) {
	    cur_val = in[index];
	    count = 0;
            time = ms_since_epoch;
	} else if (in[index] > (cur_val + _range)) {
	    cur_val = in[index];
	    count = 0;
	    time = ms_since_epoch;
	} else {
	    cur_val = in[index];
	    count += 1;
	}
	  
	if (count > 320) {
            out[index] = 1.0;
	} else {
            out[index] = 0.0;
	}
                
	if (count == 320) {
	  string str;
	  tag_key = pmt::intern("in_range");

	  str.append(to_string(cur_val));
	  str.append("@");
	  str.append(to_string(time));
	  str.append("@");
	  str.append(to_string(seq));
	  tag_value = pmt::intern(str);

	  offset = index;
	  add_item_tag(0, nitems_written(0) + offset, tag_key, tag_value);
	  seq += 1;
	}
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace etreesModule */
} /* namespace gr */

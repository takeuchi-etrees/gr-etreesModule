/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "moveTag_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace etreesModule {

using input_type = float;
using output_type = float;
moveTag::sptr moveTag::make() { return gnuradio::make_block_sptr<moveTag_impl>(); }


/*
 * The private constructor
 */
moveTag_impl::moveTag_impl()
    : gr::sync_block("moveTag",
                     gr::io_signature::make(
                         2 /* min inputs */, 2 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
moveTag_impl::~moveTag_impl() {}

int moveTag_impl::work(int noutput_items,
                       gr_vector_const_void_star& input_items,
                       gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto out = static_cast<output_type*>(output_items[0]);

    // Do <+signal processing+>
    for (int index = 0; index < noutput_items; index++) {
        out[index] = in1[index];
    }

    // get tags
    const uint64_t samp0_count = nitems_read(0);
    get_tags_in_range(
        d_tags, 0, samp0_count, samp0_count + noutput_items, pmt::mp("MAC"));

    // no tags -> no frame
    if (d_tags.empty()) {
        return noutput_items;
    }
      
    // check if frame starts at sample 0
    std::sort(d_tags.begin(), d_tags.end(), tag_t::offset_compare);
    uint64_t off = d_tags[0].offset;
    if (off != samp0_count)
        return off - samp0_count;

    add_item_tag(0, nitems_written(0) + d_tags[0].offset, d_tags[0].key, d_tags[0].value);
    std::cout << d_tags[0].key << std::endl;
    std::cout << d_tags[0].value << std::endl;
    
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace etreesModule */
} /* namespace gr */

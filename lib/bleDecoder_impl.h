/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ETREESMODULE_BLEDECODER_IMPL_H
#define INCLUDED_ETREESMODULE_BLEDECODER_IMPL_H

#include <gnuradio/etreesModule/bleDecoder.h>

namespace gr {
namespace etreesModule {

class bleDecoder_impl : public bleDecoder
{
private:
    std::string _uuid;
    std::vector<tag_t> d_tags;

public:
    bleDecoder_impl(std::string uuid);
    ~bleDecoder_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace etreesModule
} // namespace gr

#endif /* INCLUDED_ETREESMODULE_BLEDECODER_IMPL_H */

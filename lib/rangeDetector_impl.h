/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ETREESMODULE_RANGEDETECTOR_IMPL_H
#define INCLUDED_ETREESMODULE_RANGEDETECTOR_IMPL_H

#include <gnuradio/etreesModule/rangeDetector.h>

namespace gr {
namespace etreesModule {

class rangeDetector_impl : public rangeDetector
{
private:
    float _range;
    float cur_val;
    bool in_range;
    long count;
    long time;
    long seq;

public:
    rangeDetector_impl(float range);
    ~rangeDetector_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace etreesModule
} // namespace gr

#endif /* INCLUDED_ETREESMODULE_RANGEDETECTOR_IMPL_H */

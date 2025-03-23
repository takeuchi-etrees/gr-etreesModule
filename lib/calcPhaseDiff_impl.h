/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ETREESMODULE_CALCPHASEDIFF_IMPL_H
#define INCLUDED_ETREESMODULE_CALCPHASEDIFF_IMPL_H

#include <gnuradio/etreesModule/calcPhaseDiff.h>

namespace gr {
namespace etreesModule {

class calcPhaseDiff_impl : public calcPhaseDiff
{
private:
    // Nothing to declare in this block.

public:
    calcPhaseDiff_impl();
    ~calcPhaseDiff_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace etreesModule
} // namespace gr

#endif /* INCLUDED_ETREESMODULE_CALCPHASEDIFF_IMPL_H */

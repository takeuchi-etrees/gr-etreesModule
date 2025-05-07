/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ETREESMODULE_RANGEDETECTOR_H
#define INCLUDED_ETREESMODULE_RANGEDETECTOR_H

#include <gnuradio/etreesModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace etreesModule {

/*!
 * \brief <+description of block+>
 * \ingroup etreesModule
 *
 */
class ETREESMODULE_API rangeDetector : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<rangeDetector> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of etreesModule::rangeDetector.
     *
     * To avoid accidental use of raw pointers, etreesModule::rangeDetector's
     * constructor is in a private implementation
     * class. etreesModule::rangeDetector::make is the public interface for
     * creating new instances.
     */
    static sptr make(float range = 0.1);
};

} // namespace etreesModule
} // namespace gr

#endif /* INCLUDED_ETREESMODULE_RANGEDETECTOR_H */

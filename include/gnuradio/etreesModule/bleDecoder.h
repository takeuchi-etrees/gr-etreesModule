/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_ETREESMODULE_BLEDECODER_H
#define INCLUDED_ETREESMODULE_BLEDECODER_H

#include <gnuradio/etreesModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace etreesModule {

/*!
 * \brief <+description of block+>
 * \ingroup etreesModule
 *
 */
class ETREESMODULE_API bleDecoder : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<bleDecoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of etreesModule::bleDecoder.
     *
     * To avoid accidental use of raw pointers, etreesModule::bleDecoder's
     * constructor is in a private implementation
     * class. etreesModule::bleDecoder::make is the public interface for
     * creating new instances.
     */
    static sptr make(std::string uuid = "");
};

} // namespace etreesModule
} // namespace gr

#endif /* INCLUDED_ETREESMODULE_BLEDECODER_H */

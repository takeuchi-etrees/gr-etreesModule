/*
 * Copyright 2025 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(bleDecoder.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(e1f61ab2af2bc4b4a1a9ed116256fc0f)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/etreesModule/bleDecoder.h>
// pydoc.h is automatically generated in the build directory
#include <bleDecoder_pydoc.h>

void bind_bleDecoder(py::module& m)
{

    using bleDecoder    = gr::etreesModule::bleDecoder;


    py::class_<bleDecoder, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<bleDecoder>>(m, "bleDecoder", D(bleDecoder))

        .def(py::init(&bleDecoder::make),
           D(bleDecoder,make)
        )
        



        ;




}









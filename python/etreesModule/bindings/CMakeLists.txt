# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT etreesModule_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT etreesModule_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND etreesModule_python_files
    bleDecoder_python.cc
    calcPhaseDiff_python.cc
    moveTag_python.cc
    rangeDetector_python.cc python_bindings.cc)

gr_pybind_make_oot(etreesModule ../../.. gr::etreesModule "${etreesModule_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET etreesModule_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:etreesModule_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/etreesModule/)

install(
    TARGETS etreesModule_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/etreesModule
    COMPONENT pythonapi)

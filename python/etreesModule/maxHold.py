#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2025 Yoji Takeuchi.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#


import numpy as np
from gnuradio import gr

class maxHold(gr.sync_block):
    """
    docstring for block maxHold
    """
    def __init__(self, vectorSize=1024):
        gr.sync_block.__init__(self,
            name="maxHold",
            in_sig=[(np.float32, vectorSize)],
            out_sig=[(np.float32, vectorSize)])
        self.max_vector = np.full(vectorSize, np.finfo(np.float32).min, dtype=np.float32) 
        self.vectorSize = vectorSize

    def work(self, input_items, output_items):
        in0 = input_items[0]
        for sampleIndex in range(len(in0)):
            for vectorIndex in range(len(in0[sampleIndex])):
                if in0[sampleIndex][vectorIndex] > self.max_vector[vectorIndex]:
                    self.max_vector[vectorIndex] = in0[sampleIndex][vectorIndex]
        
        for sampleIndex in range(len(in0)):
            for vectorIndex in range(len(in0[sampleIndex])):
                output_items[0][sampleIndex][vectorIndex] = self.max_vector[vectorIndex]
        
        return len(output_items[0])

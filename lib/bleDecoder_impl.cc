/* -*- c++ -*- */
/*
 * Copyright 2025 Yoji Takeuchi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bleDecoder_impl.h"
#include <gnuradio/io_signature.h>
#include <iomanip>
#include <bitset>
using namespace std;

uint8_t inline SwapBits(uint8_t a){
	return (uint8_t) (((a * 0x0802LU & 0x22110LU) | (a * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16);
}


/* whiten (descramble) BTLE packet using channel value */
void BTLEWhiten(uint8_t* data, uint8_t len, uint8_t chan){

	uint8_t  i;
	uint8_t lfsr = SwapBits(chan) | 2;
	while(len--){
		for(i = 0x80; i; i >>= 1){

			if(lfsr & 0x80){

				lfsr ^= 0x11;
				(*data) ^= i;
			}
			lfsr <<= 1;
		}
		data++;
	}
}


namespace gr {
namespace etreesModule {

using input_type = uint8_t;
using output_type = uint8_t;
bleDecoder::sptr bleDecoder::make(std::string uuid)
{
    return gnuradio::make_block_sptr<bleDecoder_impl>(uuid);
}


/*
 * The private constructor
 */
bleDecoder_impl::bleDecoder_impl(std::string uuid)
    : gr::sync_block("bleDecoder",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _uuid = uuid;
}

/*
 * Our virtual destructor.
 */
bleDecoder_impl::~bleDecoder_impl() {}

int bleDecoder_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);
    const size_t N = sizeof(int) * 8;

    // Do <+signal processing+>
    for (int index = 0; index < noutput_items; index++) {
        out[index] = in[index];
    }

    // get tags
    const uint64_t samp0_count = nitems_read(0);
    get_tags_in_range(
        d_tags, 0, samp0_count, samp0_count + noutput_items, pmt::mp("ble_sync"));

    // no tags -> no frame
    if (d_tags.empty()) {
        return noutput_items;
    }
      
    // check if frame starts at sample 0
    std::sort(d_tags.begin(), d_tags.end(), tag_t::offset_compare);
    uint64_t off = d_tags[0].offset;
    if (off != samp0_count)
        return off - samp0_count;

    /*
    std::cout << std::endl << "BLE_SYNC\n";
    */
    
    uint8_t data[256];
    std::string out_text = "";

    int size = 2;

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < 8; j++) {
	if (in[i*8 + j] == 1) {
	  out_text = "1" + out_text;
	} else {
	  out_text = "0" + out_text;
	}
      }
      data[i] = SwapBits((int)bitset<N>(out_text).to_ulong());
      /*
      printf("%02X ", SwapBits(data[j]));
      */
      out_text = "";
    }

    BTLEWhiten(data, size, 38);

    /*
    printf("length = %d\n", SwapBits(data[1]) & 0x3f);
    */

    size = (SwapBits(data[1]) & 0x3f) + 2;

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < 8; j++) {
	if (in[i*8 + j] == 1) {
	  out_text = "1" + out_text;
	} else {
	  out_text = "0" + out_text;
	}
      }
      data[i] = SwapBits((int)bitset<N>(out_text).to_ulong());
      /*
      printf("%02X ", SwapBits(data[j]));
      */
      out_text = "";
    }

    BTLEWhiten(data, size, 38);

    /*
    for (int i = 0; i < size; i++) {
      printf("%02X ", SwapBits(data[i]));
    }
    printf("\n");
    */

    char mac[256];
    char uuid[256];
    if (size > 7) {
      sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X\n", SwapBits(data[7]), SwapBits(data[6]), SwapBits(data[5]), SwapBits(data[4]), SwapBits(data[3]), SwapBits(data[2]));
    }

    if (size > 33) {
      sprintf(uuid, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
	      SwapBits(data[17]), SwapBits(data[18]), SwapBits(data[19]), SwapBits(data[20]), SwapBits(data[21]), SwapBits(data[22]), SwapBits(data[23]), SwapBits(data[24]),
	      SwapBits(data[25]), SwapBits(data[26]), SwapBits(data[27]), SwapBits(data[28]), SwapBits(data[29]), SwapBits(data[30]), SwapBits(data[31]), SwapBits(data[32])
	      );
    }

    if (uuid == _uuid) {
      printf("%s\n", uuid);
      printf("HIT!\n");
      add_item_tag(0, nitems_written(0) +  8 * 8, pmt::intern("MAC"), pmt::intern(mac));
      add_item_tag(0, nitems_written(0) + 17 * 8, pmt::intern("UUID"), pmt::intern(uuid));
      add_item_tag(0, nitems_written(0) + 32 * 8, pmt::intern("UUID"), pmt::intern("END"));
      add_item_tag(0, nitems_written(0) + 38 * 8, pmt::intern("END"), pmt::intern(""));
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace etreesModule */
} /* namespace gr */

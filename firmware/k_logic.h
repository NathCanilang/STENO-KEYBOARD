#ifndef K_LOGIC_H
#define K_LOGIC_H

#include <stdint.h>
#include "config.h"
#include "defer_debounce.h"

enum BytesStatus{
    PROCESSING_INPUTS = 0,
    BYTES_READY
};

enum BytesStatus get_key_process_status();

void insert_keybit_to_bitmap(uint8_t key, unsigned char* bitmap);
void reset_array(unsigned char bitmap[]);
void process_raw_bit_input(bool raw_array[MATRIX_ROW][MATRIX_COLUMN], unsigned char buffer[], uint32_t* curr_time);
#endif
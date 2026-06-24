#ifndef LOGIC_H
#define LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

extern bool matrix_raw[MATRIX_ROW * MATRIX_COLUMN];
extern bool matrix_prev[MATRIX_ROW * MATRIX_COLUMN];

void update_processed_bitmap(uint8_t key, unsigned char* bitmap);
void reset_array(unsigned char bitmap[]);
void process_raw_bit_input(uint32_t* curr_time);
#endif
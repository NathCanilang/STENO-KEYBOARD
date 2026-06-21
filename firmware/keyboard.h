#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include "config.h"
// #include <hardware/gpio.h>

extern const size_t col_pins[MATRIX_COLUMN];
extern const size_t row_pins[MATRIX_ROW];

void send_buffer_to_host(unsigned char* buffer);
void scan_keyboard_matrix(bool raw_array[MATRIX_ROW][MATRIX_COLUMN]);

// this will be called in the main fucntion for the whole keyboard stuff
void keyboard_task(void);

#endif
#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>
#include "config.h"

extern bool matrix_raw[MATRIX_ROW * MATRIX_COLUMN];
extern bool matrix_deb[MATRIX_ROW * MATRIX_COLUMN];

void init_matrix_pin(void);
// void send_buffer_to_host(unsigned char* buffer);
bool scan_keyboard_matrix();

// this will be called in the main fucntion for the whole keyboard stuff
// void keyboard_task(void);

#endif
#ifndef LOGIC_H
#define LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

extern bool matrix_raw[MATRIX_ROW * MATRIX_COLUMN];
extern bool matrix_prev[MATRIX_ROW * MATRIX_COLUMN];

void update_bitmap(void);
bool matrix_is_empty(void);
void reset_report_buffer(void);
void process_keyboard_input(void);
#endif
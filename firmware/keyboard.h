#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include "hardware/gpio.h"

// GPIO Declarations
#define COLUMN_00_PIN 0
#define COLUMN_01_PIN 1
#define COLUMN_02_PIN 2
#define COLUMN_03_PIN 3
#define COLUMN_04_PIN 5
#define COLUMN_05_PIN 13
#define COLUMN_06_PIN 14
#define COLUMN_07_PIN 15
#define COLUMN_08_PIN 26
#define COLUMN_09_PIN 28
#define COLUMN_10_PIN 29
#define ROW_00_PIN 6
#define ROW_01_PIN 8
#define ROW_02_PIN 9
#define ROW_03_PIN 12 
#define ROW_04_PIN 11
#define ROW_05_PIN 10

#define MATRIX_ROW 6
#define MATRIX_COLUMN 11
#define REQUIRED_BYTES 4

extern const size_t col_pins[MATRIX_COLUMN];
extern const size_t row_pins[MATRIX_ROW];

// this will be called in the main fucntion for the whole keyboard stuff
void keyboard_task(void);

#endif
#ifndef HARDWARE_WRAPPER_H
#define HARDWARE_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>
#include "defer_debounce.h"

//pin utils
void init_pins(uint8_t pin);
void pin_set_dir(uint8_t pin, bool pin_dir);
bool get_pin_value(uint8_t pin);
void set_pin_output(uint8_t pin, bool output);

uint32_t get_time_us(void);

#endif
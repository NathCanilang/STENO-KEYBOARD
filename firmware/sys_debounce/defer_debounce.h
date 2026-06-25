#ifndef DEFER_DEBOUNCE_H
#define DEFER_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>
// #include "pico/stdlib.h"

bool debounce_time_elapsed(bool raw_reading[], bool debounced_reading[], bool state_changed);

#endif

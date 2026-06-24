#include "defer_debounce.h"
#include <string.h>
#include "hal.h"
#include "config.h"

bool debounce_time_elapsed(bool raw_reading[], bool debounced_reading[], bool state_changed)
{
    static uint32_t debounce_time_start;
    static bool debouncing = false;
    bool is_current_readings_changed = false;

    printf("Debouncing: %d\n", debouncing);

    size_t size = (MATRIX_ROW * MATRIX_COLUMN) * sizeof(bool);
    if(state_changed){
        debouncing = true;
        debounce_time_start = time_us();
        // printf("Time set: %d\n", time_us());
        // printf("first\n");
    }
    else if(debouncing && (time_us() - debounce_time_start) >= DEBOUNCE_TIME){
        // printf("Hit in here\n");
        if(memcmp(raw_reading, debounced_reading, size) != 0){
            memcpy(debounced_reading, raw_reading, size);
            is_current_readings_changed = true;
            // printf("debouncing done\n");
        }
        debouncing = false;
    }
    return is_current_readings_changed;
}

#ifndef DEFER_DEBOUNCE_H
#define DEFER_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>
// #include "pico/stdlib.h"

#define DEBOUNCE_TIME   10 // this is in ms

#define NUM_ROW 6
#define NUM_COLUMN 11

enum KeyStates{
    KEY_FREE = 0,
    KEY_LOCKED_OUT = 1
};

typedef struct{
    uint32_t start_time;
    enum KeyStates key_state;
    bool sample_reading;
}key_t;

extern key_t keys[NUM_ROW][NUM_COLUMN]; 

void set_key_states(uint8_t row, uint8_t col, key_t* key_states);
key_t* get_key_states(uint8_t row, uint8_t col);
void reset_key_debounce_time(uint8_t row, uint8_t col, uint32_t curr_time);
bool check_debounce_time_elapsed(key_t *key, uint32_t* curr_time, bool curr_pin_state);

#endif

/*

pseudocode:
if a key has been pressed (HIGH status)
insert the key in the bitmap
start the lockout timer
for every poll in the matrix and scanning the same key (locked out key), check the time
once the lockout timer for the key has now elapsed, lift the lockout status up
rinse and repeat


need to figure out:
- where to store the structs
- how to do a non blocking timer
- how to check time in the said timer wihout delaying the others

*/
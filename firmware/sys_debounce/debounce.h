#ifndef EAGER_DB_H
#define EAGER_DB_H

#include <stdint.h>
#include "pico/stdlib.h"

#define DEBOUNCE_TIME   5 // this is in ms

#define NUM_ROW 6
#define NUM_COLUMN 11

enum KeyStates{
    KEY_LOCKED_OUT = 0,
    KEY_FREE
};

typedef struct{
    uint32_t start_time;
    enum KeyStates state;
}__attribute__((packed)) Key;

Key keys[NUM_ROW][NUM_COLUMN]; 

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
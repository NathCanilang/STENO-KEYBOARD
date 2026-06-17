#include "defer_debounce.h"

key_t keys[NUM_ROW][NUM_COLUMN] = {0};

void set_key_states(uint8_t row, uint8_t col, key_t* key_states)
{
    keys[row][col] = *key_states;
}

key_t* get_key_states(uint8_t row, uint8_t col)
{
    return &keys[row][col];
}

void reset_key_debounce_time(uint8_t row, uint8_t col, uint32_t curr_time)
{
    keys[row][col].start_time = curr_time;
}

bool is_debounce_time_elapsed(key_t *key, uint32_t* curr_time, bool curr_pin_state)
{
    uint32_t calculated_key_time = *curr_time - key->start_time;

    if(key->key_state == KEY_HELD_DOWN){
        // this is when the user released the key it will reset the status of the key
        if(curr_pin_state == 0){
            key->key_state = KEY_FREE;
            key->sample_reading = 0; //reset the boolean just in case
            key->start_time = 0;
        }
        return false;
    }

    if(key->key_state == KEY_FREE){
        return false;
    }

    if(key->key_state == KEY_DEBOUNCING){

        if(key->sample_reading == 0){
            key->key_state = KEY_FREE;
            key->start_time = 0;
            return false;
        }

        if(calculated_key_time >= DEBOUNCE_TIME){
            key->key_state = KEY_HELD_DOWN;
            return true;
        }
        return false;
    }
    return false;
}

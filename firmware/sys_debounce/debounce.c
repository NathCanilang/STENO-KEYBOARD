#include "debounce.h"

Key keys[NUM_ROW][NUM_COLUMN];

void set_key_states(uint8_t row, uint8_t col, Key *key_states)
{
    keys[row][col] = *key_states;
}

Key get_key_states(uint8_t row, uint8_t col)
{
    return keys[row][col];
}

void reset_key_debounce_time(uint8_t row, uint8_t col, uint32_t curr_time)
{
    keys[row][col].start_time = curr_time;
}

bool check_debounce_time_elapsed(Key *key, uint32_t curr_time, bool curr_pin_state)
{
    if(key->key_state == KEY_LOCKED_OUT){ // check the key if it actually in debouncing state
        if(key->sample_reading != curr_pin_state){
            key->start_time = curr_time; // reset the timer as per algorithm
            printf("wall1\r\n");
            return false;
        }
        else{
            if((curr_time - key->start_time) >= DEBOUNCE_TIME){
                key->key_state = KEY_FREE;
                key->sample_reading = 0; //reset the boolean just in case
                key->start_time =  0;
                printf("Success1\r\n");
                return true;
            }
            else{
                printf("wall2\r\n");
                return false;
            }
        }
    }
    printf("wall3\r\n");
    return false; // this means the key has not been pressed
}

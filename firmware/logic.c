#include <string.h>
#include "logic.h"
#include "defer_debounce.h"

#define KEY_PRESSED 1
#define KEY_IDLE    0

// based on QMK's style of declaration
static const uint32_t keymaps[][MATRIX_ROW][MATRIX_COLUMN] = {
    [0] = LAYOUT(
        L_KC_S, L_KC_T, L_KC_P, L_KC_H, KC_AST,    KC_AST, R_KC_F, R_KC_P, R_KC_L, R_KC_T, R_KC_D,
        L_KC_S, L_KC_K, L_KC_W, L_KC_R, KC_AST,    KC_AST, R_KC_R, R_KC_B, R_KC_G, R_KC_S, R_KC_Z,
                        KC_HASH, L_KC_A, L_KC_O,   R_KC_E, R_KC_U, KC_HASH
    )
};

/*
TX BOLT = 00HWPKTS 01UE*OAR 10GLBPRF 110#ZDST
*/
void update_processed_bitmap(uint8_t key, unsigned char *bitmap)
{
    if(key == KC_NONE){ return; };
    
    uint8_t bitmap_index = key / 8; // bits per byte
    uint8_t input_key_flag = 1 << (key - (bitmap_index * 8));
    bitmap[bitmap_index] |= input_key_flag;
}

void reset_array(unsigned char bitmap[])
{
    //reset the TX Bolt bitmap flags placement kasi why not do it the manual way
    bitmap[0] = 0x00;
    bitmap[1] = 0x40;
    bitmap[2] = 0x80;
    bitmap[3] = 0xC0;
}

void process_raw_bit_input(uint32_t* curr_time)
{
    // bool is_state_changed = memcmp(matrix_raw, matrix_curr, sizeof(matrix_curr)) != 0;

    // if(is_state_changed){ memcpy(matrix_raw, matrix_curr, sizeof(matrix_curr)); }
    // bool is_matrix_debounced = debounce_time_elapsed(matrix_prev, matrix_raw, is_state_changed, *curr_time, (MATRIX_ROW * MATRIX_COLUMN));


    
}

/*
Problems gathered
- if the key has passed the debounced part and lifted the key it is not erased from the buffer (must add a checker if the key flags are still the same)
- machine gun input from the right T and S key (don't know why)
*/
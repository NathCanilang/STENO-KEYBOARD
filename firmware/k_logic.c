#include "k_logic.h"
#include "tusb.h" 

// based on QMK's style of declaration
static const uint32_t keymaps[][MATRIX_ROW][MATRIX_COLUMN] = {
    [0] = LAYOUT(
        L_KC_S, L_KC_T, L_KC_P, L_KC_H, KC_AST,    KC_AST, R_KC_F, R_KC_P, R_KC_L, R_KC_T, R_KC_D,
        L_KC_S, L_KC_K, L_KC_W, L_KC_R, KC_AST,    KC_AST, R_KC_R, R_KC_B, R_KC_G, R_KC_S, R_KC_Z,
                        KC_HASH, L_KC_A, L_KC_O,   R_KC_E, R_KC_U, KC_HASH
    )
};

static enum BytesStatus processing_status = PROCESSING_INPUTS;

enum BytesStatus get_key_process_status()
{
    return processing_status;
}

void insert_keybit_to_bitmap(uint8_t key, unsigned char *bitmap)
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

void process_raw_bit_input(bool raw_array[MATRIX_ROW][MATRIX_COLUMN], unsigned char buffer[], uint32_t* curr_time)
{
    static bool key_stroke_active = false;
    bool current_array_active = false;

    for(uint8_t i = 0; i < MATRIX_COLUMN; i++){
        for(uint8_t j = 0; j < MATRIX_ROW; j++){
            bool key_bit = raw_array[j][i];

            if(key_bit){
                if(get_key_states(j, i)->key_state == KEY_FREE){
                    key_t key = {
                    .sample_reading = key_bit,
                    .key_state = KEY_DEBOUNCING,
                    .start_time = *curr_time

                    };
                    set_key_states(j, i, &key);
                }
                current_array_active = true;

            }
            // if(key_bit && ((get_key_states(j, i)->key_state == KEY_FREE))){
                
            //     current_array_active = true;
            // }
            // else if(key_bit && (get_key_states(j, i)->key_state == KEY_HELD_DOWN)){
            //     current_array_active = true;
            // }
            key_t* curr_key = get_key_states(j,i);
            if(is_debounce_time_elapsed(curr_key, curr_time, key_bit)){
                insert_keybit_to_bitmap(keymaps[0][j][i], buffer);
            }
        }
    }

    if(current_array_active){
        processing_status = PROCESSING_INPUTS;
        key_stroke_active = current_array_active; 
        return;
    }
    else if(!current_array_active && key_stroke_active){
        processing_status = BYTES_READY;
        key_stroke_active = current_array_active; 
    }

    // if (current_array_active) {
    //     processing_status = PROCESSING_INPUTS;
    //     key_stroke_active = true;
    // }
    // else {
    //     if (key_stroke_active) {
    //         processing_status = BYTES_READY;
    //     }
    //     key_stroke_active = false;
    // }
}
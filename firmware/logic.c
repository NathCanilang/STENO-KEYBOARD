#include <string.h>
#include "logic.h"
#include "matrix.h"
#include "usb.h"

// based on QMK's style of declaration
static const uint32_t keymaps[][MATRIX_ROW][MATRIX_COLUMN] = {
    [0] = LAYOUT(
        L_KC_S, L_KC_T, L_KC_P, L_KC_H, KC_AST,    KC_AST, R_KC_F, R_KC_P, R_KC_L, R_KC_T, R_KC_D,
        L_KC_S, L_KC_K, L_KC_W, L_KC_R, KC_AST,    KC_AST, R_KC_R, R_KC_B, R_KC_G, R_KC_S, R_KC_Z,
                        KC_HASH, L_KC_A, L_KC_O,   R_KC_E, R_KC_U, KC_HASH
    )
};

unsigned char report_buffer[REQUIRED_BYTES] = {0x00, 0x40, 0x80, 0xC0};

/*
TX BOLT = 00HWPKTS 01UE*OAR 10GLBPRF 110#ZDST
*/
void update_bitmap(void)
{    
    for(int col = 0; col < MATRIX_COLUMN; col++){
        for(int row = 0; row < MATRIX_ROW; row++){
            bool bit = matrix_deb[(row * MATRIX_COLUMN) + col];
            if(bit){
                // char buffer[64] = "Pressed";
                // tud_cdc_write(buffer, sizeof(buffer));
                // tud_cdc_write_flush(); 

                uint8_t key = keymaps[0][row][col];
                uint8_t bitmap_index = key / 8; // bits per byte
                uint8_t input_key_flag = 1 << (key - (bitmap_index * 8));
                report_buffer[bitmap_index] |= input_key_flag;
            }
        }
    }

}

bool matrix_is_empty(void)
{
    for(size_t i = 0; i < MATRIX_ROW * MATRIX_COLUMN; i++)
    {
        if(matrix_deb[i])
            return false;
    }

    return true;
}

void reset_report_buffer(void)
{
    //reset the TX Bolt bitmap flags placement kasi why not do it the manual way
    report_buffer[0] = 0x00;
    report_buffer[1] = 0x40;
    report_buffer[2] = 0x80;
    report_buffer[3] = 0xC0;
}

void process_keyboard_input(void)
{
    static bool stroke_active = false;
    bool key_changed = scan_keyboard_matrix();

    if(!key_changed) return;

    update_bitmap();
    // printf("bitmap updated\n");
    bool is_empty = matrix_is_empty();

    if(!stroke_active && !is_empty)
    {
        // printf("stroke is currently active\n");
        stroke_active = true;
    }

    if(stroke_active && is_empty)
    {
        // printf("sending\n");
        send_packet_to_host(report_buffer);
        reset_report_buffer();
        stroke_active = false;
    }
}
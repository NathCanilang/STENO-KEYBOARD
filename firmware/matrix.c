// #include "pico/stdlib.h"
#include <string.h>
#include <stdio.h>
#include "defer_debounce.h"
#include "hal.h"
#include "stdint.h"
#include "matrix.h"

#define ARRAY_WIDTH 11
#define OUT_DIR true
#define IN_DIR  false

const size_t col_pins[MATRIX_COLUMN] = {
    COLUMN_00_PIN,  
    COLUMN_01_PIN, 
    COLUMN_02_PIN, 
    COLUMN_03_PIN, 
    COLUMN_04_PIN, 
    COLUMN_05_PIN,
    COLUMN_06_PIN,
    COLUMN_07_PIN,
    COLUMN_08_PIN,
    COLUMN_09_PIN,
    COLUMN_10_PIN
};

const size_t row_pins[MATRIX_ROW] = {
    ROW_00_PIN, 
    ROW_01_PIN, 
    ROW_02_PIN, 
    ROW_03_PIN,  
    ROW_04_PIN, 
    ROW_05_PIN 
};

bool matrix_raw[MATRIX_ROW * MATRIX_COLUMN] = { 0 };
bool matrix_deb[MATRIX_ROW * MATRIX_COLUMN] = { 0 };


// void send_buffer_to_host(unsigned char* buffer){
//     tud_cdc_write(buffer, REQUIRED_BYTES);
//     tud_cdc_write_flush(); 
// }

void init_matrix_pin(void)
{
    // intialize all rows and col pins
    for(int i = 0; i < MATRIX_COLUMN; i++){
        init_pin(col_pins[i]);
    }

    for(int i = 0; i < MATRIX_ROW; i++){
        init_pin(row_pins[i]);
    }

    // //all column pin will be output
    for(int i = 0; i < MATRIX_COLUMN; i++){
        set_pin_dir(col_pins[i], OUT_DIR);
    }

    // all the row pins will be input
    for(int i = 0; i < MATRIX_ROW; i++){
        set_pin_dir(row_pins[i], IN_DIR);
    }


    // make them all 0 for now
    for(int i = 0; i < MATRIX_COLUMN; i++){
        set_pin_state(col_pins[i], 0);
    }

    for(int i = 0; i < MATRIX_ROW; i++){
        set_pin_state(row_pins[i], 0);
    }
}

bool scan_keyboard_matrix(){
    bool curr_matrix_state [MATRIX_ROW * MATRIX_COLUMN] = {0};

    for(uint8_t col = 0; col < MATRIX_COLUMN; col++){

        set_pin_state(col_pins[col], 1); // turn on the column pin
        delay_us(2);              // stabilize the voltage

        for(uint8_t row = 0; row < MATRIX_ROW; row++){
            // raw_array[j][i] = gpio_get(row_pins[j]);
            curr_matrix_state[(row * MATRIX_COLUMN) + col] = read_pin(row_pins[row]);
        }
        set_pin_state(col_pins[col], 0);
    }

    bool changed = memcmp(curr_matrix_state, matrix_raw, sizeof(curr_matrix_state));
    if(changed) {
        // printf("matrix is changed\n");
        memcpy(matrix_raw, curr_matrix_state, sizeof(curr_matrix_state));
    }
    changed = debounce_time_elapsed(matrix_raw, matrix_deb, changed);

    return changed;
}


// void keyboard_task(void)
// {
//     uint32_t current_time = to_ms_since_boot(get_absolute_time());
//     scan_keyboard_matrix(raw_bits); 
//     process_raw_bit_input(raw_bits, report_buffer, &current_time);

//     if(get_key_process_status() == BYTES_READY){
//         send_buffer_to_host(report_buffer);
//         reset_array(report_buffer);
//     }
// }
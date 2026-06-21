#include "pico/stdlib.h"
#include "stdint.h"
#include "tusb.h" 
#include "keyboard.h"
#include "defer_debounce.h"
#include "k_logic.h"

#define ARRAY_WIDTH 11

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

static bool raw_bits[MATRIX_ROW][MATRIX_COLUMN] = {0};
static unsigned char report_buffer[REQUIRED_BYTES] = {0};

// don't do anything here
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// don't do anything here as well
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;
}

void send_buffer_to_host(unsigned char* buffer){
    tud_cdc_write(buffer, REQUIRED_BYTES);
    tud_cdc_write_flush(); 
    reset_array(buffer);
}


void scan_keyboard_matrix(bool raw_array[MATRIX_ROW][MATRIX_COLUMN]){
    for(uint8_t i = 0; i < MATRIX_COLUMN; i++){

        gpio_put(col_pins[i], 1); // turn on the column pin
        sleep_us(2);              // stabilize the voltage

        for(uint8_t j = 0; j < MATRIX_ROW; j++){
            raw_array[j][i] = gpio_get(row_pins[j]);
        }
        gpio_put(col_pins[i], 0);
    }
}

bool is_report_buffer_changed(unsigned char buffer[]){
    unsigned char default_report_buffer_values[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0 };
    bool is_buffer_changed = false;

    for(int i = 0; i < REQUIRED_BYTES; i++){
        if(buffer[i] != default_report_buffer_values[i]){
            is_buffer_changed = true;
        }
    }
    return is_buffer_changed;   
}

void keyboard_task(void)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    scan_keyboard_matrix(raw_bits); 
    process_raw_bit_input(raw_bits, report_buffer, &current_time);

    // if(is_report_buffer_changed(report_buffer)){
    //     send_buffer_to_host(report_buffer);
    //     reset_array(report_buffer);
    // }

    if(get_key_process_status() == BYTES_READY){
        send_buffer_to_host(report_buffer);
        reset_array(report_buffer);
    }
}
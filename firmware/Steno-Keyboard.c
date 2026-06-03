#include <stdlib.h>
#include <bsp/board_api.h>
#include <string.h>
#include <tusb.h>
#include <pico/stdio.h>
#include "keyboard.h"


void pin_init(void){
    // gpio_init(COLUMN_00_PIN);
    // gpio_init(COLUMN_01_PIN);
    // gpio_init(COLUMN_02_PIN);
    // gpio_init(COLUMN_03_PIN);
    // gpio_init(COLUMN_04_PIN);
    // gpio_init(COLUMN_05_PIN);
    // gpio_init(COLUMN_06_PIN);
    // gpio_init(COLUMN_07_PIN);
    // gpio_init(COLUMN_08_PIN);
    // gpio_init(COLUMN_09_PIN);
    // gpio_init(COLUMN_10_PIN);
    // gpio_init(ROW_00_PIN);
    // gpio_init(ROW_01_PIN);
    // gpio_init(ROW_02_PIN);
    // gpio_init(ROW_03_PIN);
    // gpio_init(ROW_04_PIN);
    // gpio_init(ROW_05_PIN);

    // //all column pin will be output while the row pins will be input
    // gpio_set_dir(COLUMN_00_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_01_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_02_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_03_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_04_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_05_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_06_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_07_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_08_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_09_PIN, GPIO_OUT);
    // gpio_set_dir(COLUMN_10_PIN, GPIO_OUT);

    // gpio_set_dir(ROW_00_PIN, GPIO_IN);
    // gpio_set_dir(ROW_01_PIN, GPIO_IN);
    // gpio_set_dir(ROW_02_PIN, GPIO_IN);
    // gpio_set_dir(ROW_03_PIN, GPIO_IN);
    // gpio_set_dir(ROW_04_PIN, GPIO_IN);
    // gpio_set_dir(ROW_05_PIN, GPIO_IN);    

    // // make them all 0 for now
    // gpio_put(COLUMN_00_PIN, 0);
    // gpio_put(COLUMN_01_PIN, 0);
    // gpio_put(COLUMN_02_PIN, 0);
    // gpio_put(COLUMN_03_PIN, 0);
    // gpio_put(COLUMN_04_PIN, 0);
    // gpio_put(COLUMN_05_PIN, 0);
    // gpio_put(COLUMN_06_PIN, 0);
    // gpio_put(COLUMN_07_PIN, 0);
    // gpio_put(COLUMN_08_PIN, 0);
    // gpio_put(COLUMN_09_PIN, 0);
    // gpio_put(COLUMN_10_PIN, 0);

    // gpio_pull_down(ROW_00_PIN);
    // gpio_pull_down(ROW_01_PIN);
    // gpio_pull_down(ROW_02_PIN);
    // gpio_pull_down(ROW_03_PIN);
    // gpio_pull_down(ROW_04_PIN);
    // gpio_pull_down(ROW_05_PIN);    


    for(int i = 0; i < MATRIX_COLUMN; i++){
        gpio_init(col_pins[i]);
    }

    for(int i = 0; i < MATRIX_ROW; i++){
        gpio_init(row_pins[i]);
    }

    // //all column pin will be output
    for(int i = 0; i < MATRIX_COLUMN; i++){
        gpio_set_dir(col_pins[i], GPIO_OUT);
    }

    // all the row pins will be input
    for(int i = 0; i < MATRIX_ROW; i++){
        gpio_set_dir(row_pins[i], GPIO_IN);
    }


    // make them all 0 for now
    for(int i = 0; i < MATRIX_COLUMN; i++){
        gpio_put(col_pins[i], 0);
    }

    for(int i = 0; i < MATRIX_ROW; i++){
        gpio_pull_down(row_pins[i]);
    }
}

// Invoked when CDC interface received data from host
// void tud_cdc_rx_cb(uint8_t itf)
// {
//     (void) itf;

//     uint8_t buf[64];
//     uint32_t count = tud_cdc_read(buf, sizeof(buf));

//     // Echo back to host
//     tud_cdc_write("rec: ", 5);
//     tud_cdc_write(buf, count);
//     tud_cdc_write_flush();
// }

int main(void)
{
    // Initialize TinyUSB stack
    board_init();
    tusb_init();

    pin_init();
    while (true) {
        tud_task();
        keyboard_task();
    }
    return 0;
}
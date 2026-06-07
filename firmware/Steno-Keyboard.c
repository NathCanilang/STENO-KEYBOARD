#include <stdlib.h>
#include <bsp/board_api.h>
#include <string.h>
#include <tusb.h>
#include <pico/stdio.h>
#include "keyboard.h"


void pin_init(void){
    // intialize all rows and col pins
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
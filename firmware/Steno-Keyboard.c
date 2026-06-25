#include <tusb.h>
#include <bsp/board_api.h>
#include "matrix.h"
#include "logic.h"

int main(void)
{
    // Initialize TinyUSB stack
    board_init();
    tusb_init();

    init_matrix_pin();
    
    while (true) {
        tud_task();
        // keyboard_task();
        process_keyboard_input();
    }
    return 0;
}
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "unity.h"
#include "matrix.h"
#include "defer_debounce.h"

void setUp(void){

}

void tearDown(void){

}

// bool matrix_raw_v[MATRIX_ROW * MATRIX_COLUMN] = {
//     1,0,0,0,0, 0,1,0,0,0,0,
//     0,1,0,0,0, 0,0,1,0,0,0,
//     1,0,1,0,0, 0,0,0,1,0,0,
//     0,0,0,1,0, 0,1,0,0,0,1,
//     1,0,0,0,1, 0,0,0,0,1,0,
//     0,1,0,1,0, 0,0,1,0,0,0
// };

// bool matrix_prev_v[MATRIX_ROW * MATRIX_COLUMN] = {
//     0,0,0,0,0, 0,0,0,0,0,0,
//     0,0,0,0,0, 0,0,0,0,0,0,
//     0,0,0,0,0, 0,0,0,0,0,0,
//     0,0,0,0,0, 0,0,0,0,0,0,
//     0,0,0,0,0, 0,0,0,0,0,0,
//     0,0,0,0,0, 0,0,0,0,0,0
// };



void test_debounce_logic(void){
    bool is_matrix_debounced = false;
    set_pin_state(ROW_00_PIN, 1);
    is_matrix_debounced = scan_keyboard_matrix();
    TEST_ASSERT_FALSE(is_matrix_debounced);
    set_time(10);
    is_matrix_debounced = scan_keyboard_matrix();
    TEST_ASSERT_TRUE(is_matrix_debounced);
}

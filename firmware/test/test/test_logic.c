#include <stdint.h>
#include "config.h"
#include "unity.h"
#include "logic.h"

void setUp(void){

}

void tearDown(void){

}

void test_bit_insertion(void){
    // test 1 : single inserts
    unsigned char v_bitmap[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0};
    update_processed_bitmap(L_KC_S, v_bitmap);
    unsigned char expected_values_1[REQUIRED_BYTES] = { 0x01, 0x40, 0x80, 0xC0};
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected_values_1, v_bitmap, REQUIRED_BYTES);

    reset_array(v_bitmap); // reset the main array 

    // test 2: group inserts
    update_processed_bitmap(L_KC_S, v_bitmap);
    update_processed_bitmap(L_KC_T, v_bitmap);
    update_processed_bitmap(L_KC_A, v_bitmap);
    update_processed_bitmap(L_KC_O, v_bitmap);
    update_processed_bitmap(R_KC_T, v_bitmap);
    unsigned char expected_values_2[REQUIRED_BYTES] = { 0x03, 0x46, 0x80, 0xC1};
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected_values_2, v_bitmap, REQUIRED_BYTES);

    // test 3: reset array
    reset_array(v_bitmap); // reset the main array 
    unsigned char expected_values_3[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0};
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected_values_3, v_bitmap, REQUIRED_BYTES);
}
#include "unity.h"
#include "mock_hardware_wrapper.h"
#include "defer_debounce.h"
#include "k_logic.h"
#include <stdint.h>
#include "config.h"

void setUp(void){

}

void tearDown(void){

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

void test_active_chord_logic(void){
    // simulated key presses
    bool test_raw_bits[MATRIX_ROW][MATRIX_COLUMN] = {
        { 1, 0, 0, 1, 0,  0, 0, 0, 0, 0, 0 }, // row 0
        { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 1
        { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 2
        
        { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 3
        { 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0 }, // row 4
        { 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0 }  // row 5
    };

    unsigned char test_report_buffer[REQUIRED_BYTES] = {0};
    reset_array(test_report_buffer);
    uint32_t t_init = 0;
    uint32_t t_elapsed = 5500; 

    process_raw_bit_input(test_raw_bits, test_report_buffer, &t_init);
    process_raw_bit_input(test_raw_bits, test_report_buffer, &t_elapsed);


    unsigned char expected_report_buffer[REQUIRED_BYTES] = { 0x21, 0x60, 0x82, 0xC0 };


    // printf("Byte 1: 0x%02X\n", (unsigned int)test_report_buffer[0]);
    // printf("Byte 2: 0x%02X\n", (unsigned int)test_report_buffer[1]);
    // printf("Byte 3: 0x%02X\n", (unsigned int)test_report_buffer[2]);
    // printf("Byte 4: 0x%02X\r\n", (unsigned int)test_report_buffer[3]);
    
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_report_buffer, test_report_buffer, REQUIRED_BYTES);
    bool is_changed = is_report_buffer_changed(test_report_buffer);
    TEST_ASSERT_TRUE(is_changed);
}

// void test_idle_logic(void){
//     bool test_raw_bits[MATRIX_ROW][MATRIX_COLUMN] = {
//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 0
//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 1
//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 2

//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 3
//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }, // row 4
//     { 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0 }  // row 5
//     };

//     unsigned char test_report_buffer[REQUIRED_BYTES] = {0};
//     reset_array(test_report_buffer);
//     uint32_t t = 5500;
//     process_raw_bit_input(test_raw_bits, test_report_buffer, &t);

//     unsigned char expected_report_buffer[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0 };

//     printf("Byte 1: 0x%02X\n", (unsigned int)test_report_buffer[0]);
//     printf("Byte 2: 0x%02X\n", (unsigned int)test_report_buffer[1]);
//     printf("Byte 3: 0x%02X\n", (unsigned int)test_report_buffer[2]);
//     printf("Byte 4: 0x%02X\r\n", (unsigned int)test_report_buffer[3]);

    
//     TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_report_buffer, test_report_buffer, REQUIRED_BYTES);
// }

void test_debounce_checker(){
    key_t key = {
        .sample_reading = true,
        .key_state = KEY_DEBOUNCING,
        .start_time = 0
    };
    set_key_states(0, 0, &key);
    set_key_states(1, 0, &key);
    set_key_states(2, 0, &key);

    uint32_t t = 6000;
    int count = 0;
    for(uint8_t i = 0; i < MATRIX_COLUMN; i++){
        for(uint8_t j = 0; j < MATRIX_ROW; j++){
            key_t *curr_key = get_key_states(j,i);
            if(is_debounce_time_elapsed(curr_key, &t, true)){ // simulate that the time has elapsed and the reading is HIGH = true
                count++;
            }
        }
    }
    TEST_ASSERT_EQUAL_INT(3, count);
}

void test_reset(void){
    unsigned char test_report_buffer[REQUIRED_BYTES] = {0};
    reset_array(test_report_buffer);

    unsigned char expected_report_buffer[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0};

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_report_buffer, test_report_buffer, REQUIRED_BYTES);
}

void test_debounce_on_free_key(void){
    key_t test_key = {
        .start_time = 1000,
        .key_state = KEY_FREE,
        .sample_reading = true

    };

    uint32_t t = 1500;
    bool test_res = is_debounce_time_elapsed(&test_key, &t, false);
    printf("test: %d\n\r", test_key.start_time);

    TEST_ASSERT_FALSE(test_res);
    printf("First test done\r\n");
}

void test_bouncing_signal_on_debounce(void)
{
    key_t test_key1 = {
        .start_time = 0,
        .key_state = KEY_DEBOUNCING,
        .sample_reading = true
    };

    uint32_t current_time = 0;
    bool result = false;

    // bounce sequence
    result = is_debounce_time_elapsed(&test_key1, &current_time, false);

    current_time = 1000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, true);

    current_time = 2000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, false);

    current_time = 3000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, true);

    current_time = 4500;
    result = is_debounce_time_elapsed(&test_key1, &current_time, false);

    current_time = 6000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, true);

    current_time = 8000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, true);

    current_time = 10000;
    result = is_debounce_time_elapsed(&test_key1, &current_time, true);

    printf("RESULTS| Start Time: %u, State: %d, Sample: %d\n",
           test_key1.start_time,
           test_key1.key_state,
           test_key1.sample_reading);

    TEST_ASSERT_FALSE(result);
}

void test_bitmap_insertion(void){
    
    uint8_t key = 0x00;
    uint8_t bitmap_index = key / 8; // bits per byte
    uint8_t input_key_flag = 1 << (key - (bitmap_index * 8));
    
    printf("Flag: 0x%X", input_key_flag);
    TEST_ASSERT_EQUAL_INT8(input_key_flag, 1);
}

void test_bitmap_retreival(void){
    unsigned char test_report_buffer[REQUIRED_BYTES] = {0x03, 0x40, 0x80, 0xC0};

    // unsigned char expected_report_buffer[REQUIRED_BYTES] = { 0x00, 0x40, 0x80, 0xC0};

    bool test_1 = get_bit_in_bitmap(L_KC_T, test_report_buffer); // TRUE
    bool test_2 = get_bit_in_bitmap(L_KC_S, test_report_buffer); // TRUE
    bool test_3 = get_bit_in_bitmap(L_KC_H, test_report_buffer); // FALSE

    TEST_ASSERT_TRUE(test_1);
    TEST_ASSERT_TRUE(test_2);
    TEST_ASSERT_FALSE(test_3);
}
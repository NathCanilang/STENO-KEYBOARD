#include "unity.h"
#include "mock_hardware_wrapper.h"
#include "debounce.h"

void setUp(void){

}

void tearDown(void){

}

void test_debounce_on_free_key(void){
        Key test_key = {
        .start_time = 1000,
        .key_state = KEY_FREE,
        .sample_reading = true

    };

    bool test_res = check_debounce_time_elapsed(&test_key, 1500, false);
    printf("test: %d\n\r", test_key.start_time);

    TEST_ASSERT_FALSE(test_res);
    printf("First test done\r\n");


}

void test_bouncing_signal_on_debounce(void){
    bool test_res = false;
    // on press state
    Key test_key1 = {
        .start_time = 0,
        .key_state = KEY_LOCKED_OUT,
        .sample_reading = true
    };
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);


    test_res = check_debounce_time_elapsed(&test_key1, 1000, false);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 2000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 3000, false);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 4000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 4500, false);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 5000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 6000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    test_res = check_debounce_time_elapsed(&test_key1, 7000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);


    test_res = check_debounce_time_elapsed(&test_key1, 8000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);


    test_res = check_debounce_time_elapsed(&test_key1, 9000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);


    test_res = check_debounce_time_elapsed(&test_key1, 10000, true);
    printf("RESULTS| Start Time: %d, Key State: %d, Sample Reading: %d\n", test_key1.start_time, test_key1.key_state, test_key1.sample_reading);

    // printf("test: %d\n\r", test_key1.start_time);


    TEST_ASSERT_TRUE(test_res);    
}




// logic test will be implemented later
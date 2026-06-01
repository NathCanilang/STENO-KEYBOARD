#include "tusb.h"
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// GPIO Declarations
#define COLUMN_00_PIN 0
#define COLUMN_01_PIN 1
#define COLUMN_02_PIN 2
#define COLUMN_03_PIN 3
#define COLUMN_04_PIN 5
#define COLUMN_05_PIN 13
#define COLUMN_06_PIN 14
#define COLUMN_07_PIN 15
#define COLUMN_08_PIN 26
#define COLUMN_09_PIN 28
#define COLUMN_10_PIN 29
#define ROW_00_PIN 6
#define ROW_01_PIN 8
#define ROW_02_PIN 9
#define ROW_03_PIN 12 
#define ROW_04_PIN 11
#define ROW_05_PIN 10

#define REQUIRED_BYTES 4


typedef struct{
    unsigned char report_buffer[REQUIRED_BYTES];
} KeyboardBitmap;


uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize);
void insert_keybit_to_bitmap(uint8_t key, KeyboardBitmap *curr_bitmap);
bool tud_hid_report(uint8_t report_id, void const* report, uint16_t len);


// this will be called in the main fucntion for the whole keyboard stuff
void keyboard_task(void);

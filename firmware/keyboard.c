#include "pico/stdlib.h"
#include "stdint.h"
#include "tusb.h" 
#include "keyboard.h"
#include "debounce.h"

#define KC_NONE       0    // declare when key is empty 

// TX Bolt Approach
// Byte 1
#define L_KC_H        0x05
#define L_KC_W        0x04
#define L_KC_P        0x03
#define L_KC_K        0x02
#define L_KC_T        0x01
#define L_KC_S        0x00

// Byte 2
#define R_KC_U        0x0D
#define R_KC_E        0x0C
#define KC_AST        0x0B
#define L_KC_O        0x0A
#define L_KC_A        0x09
#define L_KC_R        0x08

// Byte 3
#define R_KC_G        0x15
#define R_KC_L        0x14
#define R_KC_B        0x13
#define R_KC_P        0x12
#define R_KC_R        0x11
#define R_KC_F        0x10

// Byte 4
#define KC_HASH       0x1C 
#define R_KC_Z        0x1B
#define R_KC_D        0x1A
#define R_KC_S        0x19 
#define R_KC_T        0x18 


// based on QMK's style of declaration
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

#define LAYOUT(\
    k00, k01, k02, k03, k04,     k05, k06, k07, k08, k09, k10,\
    k11, k12, k13, k14, k15,     k16, k17, k18, k19, k20, k21,\
              k22, k23, k24,     k25, k26, k27\
) \
{ \
    /* ROW 0: Left Half (Cols 0-4). */ \
    { k00, k01, k02, k03, k04,     KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE }, \
    /* ROW 1: Left Half (Cols 0-4). */ \
    { k11, k12, k13, k14, k15,     KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE }, \
    /* ROW 2: Left Half (Cols 2-4).*/ \
    { KC_NONE, k22, k23, k24,   KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE }, \
    \
    /* ROW 3: Right Half (Cols 5-10) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,   k05, k06, k07, k08, k09, k10 }, \
    /* ROW 4: Right Half (Cols 5-10) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,   k16, k17, k18, k19, k20, k21 }, \
    /* ROW 5: Right Half (Cols 5-7) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,   k25, k26, k27, KC_NONE, KC_NONE } \
}

// based on QMK's style of declaration
static const uint32_t keymaps[][MATRIX_ROW][MATRIX_COLUMN] = {
    [0] = LAYOUT(
        L_KC_S, L_KC_T, L_KC_P, L_KC_H, KC_AST,    KC_AST, R_KC_F, R_KC_P, R_KC_L, R_KC_T, R_KC_D,
        L_KC_S, L_KC_K, L_KC_W, L_KC_R, KC_AST,    KC_AST, R_KC_R, R_KC_B, R_KC_G, R_KC_S, R_KC_Z,
                        KC_HASH, L_KC_A, L_KC_O,   R_KC_E, R_KC_U, KC_HASH
    )
};
typedef struct{
    unsigned char report_buffer[REQUIRED_BYTES];
    unsigned char temp_bitmap[REQUIRED_BYTES]; // will be used to hold all the bits before finalizing it to the actual bitmap
} KeyboardBitmap;

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


static KeyboardBitmap bitmap = {0};
void insert_keybit_to_bitmap(uint8_t key, KeyboardBitmap *curr_bitmap)
{
    if(key == KC_NONE){ return; };
    
    uint8_t bitmap_index = key / 8; // bits per byte
    uint8_t input_key_flag = 1 << (key - (bitmap_index * 8));
    curr_bitmap->report_buffer[bitmap_index] |= input_key_flag;
}

static void reset_array(KeyboardBitmap* bitmap){
    //reset the TX Bolt bitmap flags placement kasi why not do it the manual way
    bitmap->report_buffer[0] = 0x00;
    bitmap->report_buffer[1] = 0x40;
    bitmap->report_buffer[2] = 0x80;
    bitmap->report_buffer[3] = 0xC0;

    // reset the temp bitmap to all 0 since we don't need the TX Bolt sepcific flags yet
    memset(&bitmap->temp_bitmap, 0, sizeof(bitmap->temp_bitmap));
}


// TODO: Implement proper debounce logic
void keyboard_task(void)
{
    static bool key_stroke_active = false;
    bool current_scan_active  = false;

    for (int i = 0; i < MATRIX_COLUMN; ++i)
    {
        gpio_put(col_pins[i], 1); // turn on the column pin
        sleep_us(2);              // stabilize the voltage

        for (int j = 0; j < MATRIX_ROW; ++j)
        {
            bool pin_state = gpio_get(row_pins[j]);
            Key* key = &keys[j][i]; //access the specific HIGH key
            uint32_t current_time = to_ms_since_boot(get_absolute_time()); 

            if (pin_state == true) // this is referring to HIGH
            {

                /*
                Piss poor debounce attempt
                */

                if(key->key_state == KEY_FREE){
                    
                    //start the key lockdown
                    key->start_time = current_time;
                    key->key_state = KEY_LOCKED_OUT;
                }       

                // horrible code in here
                if((key->key_state == KEY_LOCKED_OUT) && ((current_time - key->start_time) >= DEBOUNCE_TIME)){
                    key->key_state = KEY_FREE;
                    insert_keybit_to_bitmap(keymaps[0][j][i], &bitmap); // immediately store the result
                }

                // sleep_ms(5); // temporary debounce
                current_scan_active = true;
            }

            else
            {
                keys[j][i].key_state = KEY_FREE; // release resets
            }

        }

        gpio_put(col_pins[i], 0);
    }

    if(current_scan_active){
        key_stroke_active = current_scan_active; 
        return; // don't attempt to send the bitmap since the chord is not yet done
    }

    if(!current_scan_active && key_stroke_active){
        tud_cdc_write(&bitmap.report_buffer, REQUIRED_BYTES);
        tud_cdc_write_flush(); 
        reset_array(&bitmap);

    }
    key_stroke_active = current_scan_active; 
}
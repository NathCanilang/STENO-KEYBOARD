
// keyboard layout
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
    { KC_NONE, KC_NONE, k22, k23, k24,   KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE }, \
    \
    /* ROW 3: Right Half (Cols 5-10) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,   k05, k06, k07, k08, k09, k10 }, \
    /* ROW 4: Right Half (Cols 5-10) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,   k16, k17, k18, k19, k20, k21 }, \
    /* ROW 5: Right Half (Cols 5-7) */ \
    { KC_NONE, KC_NONE, KC_NONE, KC_NONE, KC_NONE,    k25, k26, k27, KC_NONE, KC_NONE, KC_NONE } \
}

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

//bitmap configs
#define MATRIX_ROW 6
#define MATRIX_COLUMN 11
#define REQUIRED_BYTES 4

// TX Bolt Approach
#define KC_NONE       0xFF    // declare when key is empty 

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
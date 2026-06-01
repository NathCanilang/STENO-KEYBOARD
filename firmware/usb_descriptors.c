#include <string.h>
#include "usb_descriptors.h"
#include "tusb.h"
#include "bsp/board_api.h"

// VID and slightly modified PID to bypass Windows caching
#define CDC_EXAMPLE_VID     0xCafe
#define CDC_EXAMPLE_PID     0x4001
#define CDC_EXAMPLE_BCD     0x0200

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + CFG_TUD_CDC * TUD_CDC_DESC_LEN + TUD_HID_DESC_LEN)

#define EPNUM_CDC_0_NOTIF   0x81
#define EPNUM_CDC_0_OUT     0x02
#define EPNUM_CDC_0_IN      0x82
#define EPNUM_HID           0x83

#define REPORT_ID           0x4
#define REPORT_BYTES        27

enum {
    ITF_NUM_CDC_0 = 0,
    ITF_NUM_CDC_0_DATA,
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

enum {
    STRID_LANGID = 0,
    STRID_MANUFACTURER,
    STRID_PRODUCT,
    STRID_SERIAL,
    STRID_CDC_0,
};

tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = CDC_EXAMPLE_BCD,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = CDC_EXAMPLE_VID,
    .idProduct          = CDC_EXAMPLE_PID,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

//NKRO HID usb_descriptor (will remove this since i am using TX bolt)
uint8_t const desc_hid_report[] =
{
        0x05, 0x01,                     // Usage Page (Generic Desktop),
        0x09, 0x06,                     // Usage (Keyboard),
        0xA1, 0x01,                     // Collection (Application),
        0x85, REPORT_ID,                // Report ID

        // bitmap of modifiers 
        0x75, 0x01,                     // Report Size (1),
        0x95, 0x08,                     // Report Count (8),
        0x05, 0x07,                     // Usage Page (Key Codes),
        0x19, 0xE0,                     // Usage Minimum (224),
        0x29, 0xE7,                     // Usage Maximum (231),
        0x15, 0x00,                     // Logical Minimum (0),
        0x25, 0x01,                     // Logical Maximum (1),
        0x81, 0x02,                     // Input (Data, Variable, Absolute), ;Modifier byte

        // bitmap of keys
        0x95, (REPORT_BYTES-1)*8,       // Report Count (),
        0x75, 0x01,                     // Report Size (1),
        0x15, 0x00,                     // Logical Minimum (0),
        0x25, 0x01,                     // Logical Maximum(1),
        0x05, 0x07,                     // Usage Page (Key Codes),
        0x19, 0x00,                     // Usage Minimum (0),
        0x29, (REPORT_BYTES-1)*8-1,     // Usage Maximum (),
        0x81, 0x02,                     // Input (Data, Variable, Absolute),
        0xc0                            // End Collection
};

uint8_t const desc_configuration[] = {
    TUD_CONFIG_DESCRIPTOR(1, 
                        ITF_NUM_TOTAL, 
                        0, 
                        CONFIG_TOTAL_LEN, 
                        0x80, 
                        100),

    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC_0, 
                        4, 
                        EPNUM_CDC_0_NOTIF, 
                        8, 
                        EPNUM_CDC_0_OUT, 
                        EPNUM_CDC_0_IN, 
                        64),

    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 
                        0, 
                        HID_ITF_PROTOCOL_NONE, 
                        sizeof(desc_hid_report), 
                        EPNUM_HID, 
                        CFG_TUD_HID_EP_BUFSIZE, 
                        5)
};

char const *string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 }, 
    "StenoProject",                 
    "Steno-Keyboard",                  
    NULL,                           
    "Steno CDC Data",                   
};

static uint16_t _desc_str[32 + 1];

uint8_t const *tud_descriptor_device_cb(void) {
    return (uint8_t const *)&desc_device;
}

uint8_t const *tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    (void)instance;
    return desc_hid_report;
}


uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;
    size_t char_count;

    switch (index) {
        case STRID_LANGID:
            memcpy(&_desc_str[1], string_desc_arr[STRID_LANGID], 2);
            char_count = 1;
            break;

        case STRID_SERIAL:
            char_count = board_usb_get_serial(_desc_str + 1, 32);
            break;

        default:
            if (!(index < sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) {
                return NULL;
            }
            const char *str = string_desc_arr[index];
            char_count = strlen(str);
            size_t const max_count = sizeof(_desc_str) / sizeof(_desc_str[0]) - 1;
            if (char_count > max_count) char_count = max_count;

            for (size_t i = 0; i < char_count; i++) {
                _desc_str[1 + i] = str[i];
            }
            break;
    }

    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (char_count * 2 + 2));
    return _desc_str;
}
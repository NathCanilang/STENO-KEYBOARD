#include "usb.h"
#include "tusb.h"
#include "config.h"

// // don't do anything here
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

void send_packet_to_host(void)
{
    unsigned char buffer[REQUIRED_BYTES];
    tud_cdc_write(buffer, REQUIRED_BYTES);
    tud_cdc_write_flush(); 
}

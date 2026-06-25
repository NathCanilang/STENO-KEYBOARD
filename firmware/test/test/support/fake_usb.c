#include <stdio.h>
#include "usb.h"

void send_packet_to_host(unsigned char buffer[])
{
    printf("Packet sent: 0x%X 0x%X 0x%X 0x%X\n", buffer[0], buffer[1], buffer[2], buffer[3]);
}

#include "hal.h"
#include <stdio.h>

static uint32_t time = 0;
static bool virtual_pins[30] = {0};

void init_pin(uint8_t pin){ }

void set_pin_state(uint8_t pin, bool state){
    virtual_pins[pin] = state;
}

void set_pin_dir(uint8_t pin, bool dir){}

void pull_down_pin(uint8_t pin){}

bool read_pin(uint8_t pin){
    return virtual_pins[pin];
}

void delay_us(uint32_t us){
    time += us;
}

uint32_t time_us(void){
    return time;
}

void set_time(uint32_t us){
    time += us;
}
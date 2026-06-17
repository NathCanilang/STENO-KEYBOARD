#include "hardware_wrapper.h"
#include <string.h>
#include <pico/stdio.h>
#include <hardware/gpio.h>
#include <pico/time.h>

#define PIN_COUNT 20

static bool mock_pins[PIN_COUNT] = { 0 }; //declare all pins as 0 output first
static uint32_t mock_time = 0;

void init_pins(uint8_t pin)
{
    gpio_init(pin);
}

void pin_set_dir(uint8_t pin, bool pin_dir)
{
    gpio_set_dir(pin, pin_dir);
}

bool get_pin_value(uint8_t pin)
{
    return gpio_get(pin);
}

void set_pin_output(uint8_t pin, bool output)
{
    gpio_put(pin, output);
}

uint32_t get_time_us(void)
{
    return to_ms_since_boot(get_absolute_time());
}


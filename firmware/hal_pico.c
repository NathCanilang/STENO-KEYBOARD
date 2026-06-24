#include "hal.h"
#include <hardware/gpio.h>
#include <pico/time.h>

void init_pin(uint8_t pin)
{
    gpio_init(pin);
}

void set_pin_state(uint8_t pin, bool state)
{
    gpio_put(pin, state);
}

void set_pin_dir(uint8_t pin, bool dir)
{
    gpio_set_dir(pin, dir);
}

void pull_down_pin(uint8_t pin)
{
    gpio_pull_down(pin);
}

bool read_pin(uint8_t pin)
{
    return gpio_get(pin);
}

void delay_us(uint32_t us)
{
    sleep_us(us);
}

uint32_t time_us(void)
{
    return to_us_since_boot(get_absolute_time());
}

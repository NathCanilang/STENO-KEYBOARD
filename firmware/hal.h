#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

void init_pin(uint8_t pin);
void set_pin_state(uint8_t pin, bool state);
void set_pin_dir(uint8_t pin, bool dir);
void pull_down_pin(uint8_t pin);
bool read_pin(uint8_t pin);
void delay_us(uint32_t us);
uint32_t time_us(void);

#endif
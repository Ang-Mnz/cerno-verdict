#ifndef STATUS_LED_H
#define STATUS_LED_H

#include "esp_err.h"

esp_err_t status_led_init(void);
esp_err_t status_led_on(void);
esp_err_t status_led_off(void);

#endif
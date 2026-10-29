#include "status_led.h"

#include "driver/gpio.h"

#define LED_GPIO GPIO_NUM_2

esp_err_t status_led_init(void)
{
    const gpio_config_t gpio_config_data = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    esp_err_t err = gpio_config(&gpio_config_data);

    if (err != ESP_OK)
    {
        return err;
    }

    return gpio_set_level(LED_GPIO, 0);
}

esp_err_t status_led_on(void)
{
    return gpio_set_level(LED_GPIO, 1);
}

esp_err_t status_led_off(void)
{
    return gpio_set_level(LED_GPIO, 0);
}
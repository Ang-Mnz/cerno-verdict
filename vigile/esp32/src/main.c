#include <string.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "uart.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_2
#define COMMAND_SIZE 16

void app_main(void)
{
    ESP_LOGI("CERNO", "Demarrage de l'application");

    uart_init();

    const gpio_config_t gpio_config_data = {
        .pin_bit_mask = 1ULL << LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    ESP_ERROR_CHECK(gpio_config(&gpio_config_data));
    ESP_ERROR_CHECK(gpio_set_level(LED_GPIO, 0));

    char command[COMMAND_SIZE];

    while (1)
    {
        uart_receive_string(command, sizeof(command));

        if (strcmp(command, "MOTION") == 0)
        {
            gpio_set_level(LED_GPIO, 1);
            ESP_LOGI("CERNO", "Mouvement detecte");
        }
        else if (strcmp(command, "CLEAR") == 0)
        {
            gpio_set_level(LED_GPIO, 0);
            ESP_LOGI("CERNO", "Fin du mouvement");
        }
        else
        {
            ESP_LOGW("CERNO", "Commande inconnue");
        }
    }
}
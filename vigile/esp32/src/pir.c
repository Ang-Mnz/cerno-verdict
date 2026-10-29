#include "pir.h"

#include "driver/gpio.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "communication.h"

#define PIR_GPIO GPIO_NUM_27

static const char *TAG = "PIR";

static void pir_task(void *arg)
{
    int previous_level = 0;

    while (1)
    {
        int current_level = gpio_get_level(PIR_GPIO);

        if (current_level == 1 && previous_level == 0)
        {
            ESP_LOGI(TAG, "Mouvement detecte par le PIR");

            esp_err_t err = communication_send_string("ACTIVATE");

            if (err != ESP_OK)
            {
                ESP_LOGE(TAG, "Echec de l'envoi de la commande ACTIVATE");
            }
        }
        else if (current_level == 0 && previous_level == 1)
        {
            ESP_LOGI(TAG, "Fin de detection du PIR");
        }

        previous_level = current_level;

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

esp_err_t pir_init(void)
{
    const gpio_config_t gpio_config_data = {
        .pin_bit_mask = 1ULL << PIR_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    esp_err_t err = gpio_config(&gpio_config_data);

    if (err != ESP_OK)
    {
        return err;
    }

    BaseType_t task_created = xTaskCreate(
        pir_task,
        "pir_task",
        2048,
        NULL,
        5,
        NULL
    );

    if (task_created != pdPASS)
    {
        ESP_LOGE(TAG, "Impossible de creer la tache PIR");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Capteur PIR initialise sur GPIO %d", PIR_GPIO);

    return ESP_OK;
}
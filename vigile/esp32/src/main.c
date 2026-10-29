#include <string.h>

#include "esp_err.h"
#include "esp_log.h"

#include "communication.h"
#include "pir.h"
#include "status_led.h"

#define COMMAND_SIZE 16

static const char *TAG = "CERNO";

void app_main(void)
{
    ESP_LOGI(TAG, "Demarrage de l'application");

    ESP_ERROR_CHECK(status_led_init());
    ESP_ERROR_CHECK(pir_init());

    communication_init();

    char command[COMMAND_SIZE];

    while (1)
    {
        communication_receive_string(command, sizeof(command));

        if (strcmp(command, "MOTION") == 0)
        {
            ESP_ERROR_CHECK(status_led_on());
            ESP_LOGI(TAG, "Mouvement detecte");
        }
        else if (strcmp(command, "CLEAR") == 0)
        {
            ESP_ERROR_CHECK(status_led_off());
            ESP_LOGI(TAG, "Fin du mouvement");
        }
        else
        {
            ESP_LOGW(TAG, "Commande inconnue");
        }
    }
}
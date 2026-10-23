#include "wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "config/wifi_secrets.h"

// Connecté ou non
#define WIFI_CONNECTED_BIT BIT0

// Nom pour les logs
static const char *TAG = "VIGILE_WIFI";

// Pour manipuler des groupes d'évenements
// Permet à plusieurs tâches de partager des états sous forme de bits et d'attendre qu'un ou plusieurs de ces états deviennent actifs.
// Dans notre cas permet à une tâche d'attendre la connexion Wi-Fi sans vérifier constamment son état.
static EventGroupHandle_t wifi_event_group;


static void wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data)
{
    (void)arg;

    if (event_base == WIFI_EVENT)
    {
        if (event_id == WIFI_EVENT_STA_START)
        {
            ESP_LOGI(TAG, "Connexion au Wi-Fi...");
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            xEventGroupClearBits(
                wifi_event_group,
                WIFI_CONNECTED_BIT);

            ESP_LOGW(TAG, "Wi-Fi deconnecte, nouvelle tentative...");
            esp_wifi_connect();
        }
    }
    else if (event_base == IP_EVENT &&
             event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;

        ESP_LOGI(
            TAG,
            "Adresse IP obtenue : " IPSTR,
            IP2STR(&event->ip_info.ip));

        xEventGroupSetBits(
            wifi_event_group,
            WIFI_CONNECTED_BIT);
    }
}

void wifi_init(void)
{
    // Création du groupe
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(
        wifi_event_group == NULL ? ESP_ERR_NO_MEM : ESP_OK);

    // Stockage NVS (système de stockage persistant fourni par ESP-IDF)
    // Permet entre autre de conserver des données entre les redémarrages
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
        err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);

    // Initialisation des composants réseaux

    // Init interface réseau
    ESP_ERROR_CHECK(esp_netif_init());
    // Init boucle d'évenement
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // Mode station (l'ESP32 se connecte à un réseau Wi-Fi existant, comme un ordinateur)
    esp_netif_create_default_wifi_sta();

    // Init pilote wifi
    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    // Enregistrement de notre fonction dans le gestionnaire d'événement
    // Les évenements proviennent de ESP-IDF
    ESP_ERROR_CHECK(
        esp_event_handler_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            wifi_event_handler,
            NULL));

    ESP_ERROR_CHECK(
        esp_event_handler_register(
            IP_EVENT,
            IP_EVENT_STA_GOT_IP,
            wifi_event_handler,
            NULL));

    // Config nom et mdp du réseau
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
        },
    };

    // Pour rejoindre le réseau existant
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    // Application de la config
    ESP_ERROR_CHECK(
        esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    // Démarrer le wifi
    ESP_ERROR_CHECK(esp_wifi_start());
}


void wifi_wait_connected(void)
{
    xEventGroupWaitBits(
        wifi_event_group,
        WIFI_CONNECTED_BIT,
        pdFALSE,
        pdTRUE,
        portMAX_DELAY);
}
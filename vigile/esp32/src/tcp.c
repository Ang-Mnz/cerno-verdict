#include "tcp.h"

#include <errno.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"

#include "esp_log.h"

#include "lwip/inet.h"
#include "lwip/sockets.h"

#include "config/tcp_config.h"
#include "wifi.h"

static const char *TAG = "VIGILE_TCP";

static int server_fd = -1;
static int client_fd = -1;


void vigile_tcp_init(void)
{
    // Initialisation wifi
    wifi_init();
    wifi_wait_connected();

    // Création de socket TCP
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (server_fd < 0)
    {
        ESP_LOGE(TAG, "Impossible de creer le socket TCP : errno=%d", errno);
        ESP_ERROR_CHECK(ESP_FAIL);
    }

    // Configuration du comportement d'un socket
    // SO_REUSEADDR pour autoriser la réutillisation de l'adresse
    const int reuse_address = 1;

    setsockopt(
        server_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &reuse_address,
        sizeof(reuse_address));

    // Définir l'adresse du serveur
    const struct sockaddr_in server_address = {
        .sin_family = AF_INET,
        .sin_port = htons(TCP_PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    // Association de l'adresse au socket
    if (bind(
            server_fd,
            (struct sockaddr *)&server_address,
            sizeof(server_address)) < 0)
    {
        ESP_LOGE(TAG, "Echec de bind : errno=%d", errno);
        ESP_ERROR_CHECK(ESP_FAIL);
    }

    // Mettre le serveur en écoute
    if (listen(server_fd, TCP_BACKLOG) < 0)
    {
        ESP_LOGE(TAG, "Echec de listen : errno=%d", errno);
        ESP_ERROR_CHECK(ESP_FAIL);
    }

    ESP_LOGI(TAG, "Serveur TCP en ecoute sur le port %d", TCP_PORT);
}

void vigile_tcp_receive_string(char *buffer, size_t size)
{
    if (size == 0)
    {
        return;
    }

    buffer[0] = '\0';

    while (1)
    {
        if (client_fd < 0)
        {
            ESP_LOGI(TAG, "En attente d'une connexion TCP...");

            client_fd = accept(server_fd, NULL, NULL);

            if (client_fd < 0)
            {
                ESP_LOGE(TAG, "Echec de accept : errno=%d", errno);
                vTaskDelay(pdMS_TO_TICKS(100));
                continue;
            }

            ESP_LOGI(TAG, "Client TCP connecte");
        }

        size_t i = 0;
        int disconnected = 0;

        while (i < size - 1)
        {
            char c;

            int received = recv(client_fd, &c, 1, 0);

            if (received <= 0)
            {
                disconnected = 1;
                break;
            }

            if (c == '\r')
            {
                continue;
            }

            if (c == '\n')
            {
                if (i > 0)
                {
                    break;
                }

                continue;
            }

            buffer[i++] = c;
        }

        buffer[i] = '\0';

        if (disconnected)
        {
            ESP_LOGW(TAG, "Client TCP deconnecte");

            close(client_fd);
            client_fd = -1;

            buffer[0] = '\0';
            continue;
        }

        return;
    }
}

esp_err_t vigile_tcp_send_string(const char *message)
{
    if (message == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if (client_fd < 0)
    {
        ESP_LOGE(TAG, "Impossible d'envoyer : aucun client TCP connecte");
        return ESP_FAIL;
    }

    size_t size = strlen(message);
    size_t sent = 0;

    while (sent < size)
    {
        int result = send(
            client_fd,
            message + sent,
            size - sent,
            0
        );

        if (result <= 0)
        {
            ESP_LOGE(TAG, "Echec de send : errno=%d", errno);
            return ESP_FAIL;
        }

        sent += result;
    }

    const char newline = '\n';

    if (send(client_fd, &newline, 1, 0) != 1)
    {
        ESP_LOGE(TAG, "Echec de l'envoi du retour a la ligne");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Message TCP envoye : %s", message);

    return ESP_OK;
}
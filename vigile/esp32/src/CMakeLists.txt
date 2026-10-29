idf_component_register(
    SRCS
        "main.c"
        "uart.c"
        "communication.c"
        "wifi.c"
        "tcp.c"
        "pir.c"
        "status_led.c"
    INCLUDE_DIRS "../include"
    REQUIRES
        driver
        esp_wifi
        esp_event
        esp_netif
        nvs_flash
        lwip
)
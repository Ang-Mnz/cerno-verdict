#ifndef TCP_H
#define TCP_H

#include <stddef.h>

#include "esp_err.h"

void vigile_tcp_init(void);
void vigile_tcp_receive_string(char *buffer, size_t size);
esp_err_t vigile_tcp_send_string(const char *message);

#endif
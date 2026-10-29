#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stddef.h>

#include "esp_err.h"

void communication_init(void);
void communication_receive_string(char *buffer, size_t size);
esp_err_t communication_send_string(const char *message);

#endif
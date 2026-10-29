#include "communication.h"
#include "config/communication_config.h"

#if COMMUNICATION_MODE == COMMUNICATION_UART

#include "uart.h"

void communication_init(void)
{
    uart_init();
}

void communication_receive_string(char *buffer, size_t size)
{
    uart_receive_string(buffer, size);
}

esp_err_t communication_send_string(const char *message)
{
    return vigile_tcp_send_string(message);
}

#elif COMMUNICATION_MODE == COMMUNICATION_TCP

#include "tcp.h"

void communication_init(void)
{
    vigile_tcp_init();
}

void communication_receive_string(char *buffer, size_t size)
{
    vigile_tcp_receive_string(buffer, size);
}

esp_err_t communication_send_string(const char *message)
{
    return vigile_tcp_send_string(message);
}


#else
#error "Mode de communication inconnu"
#endif
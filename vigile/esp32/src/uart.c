#include "uart.h"

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void uart_init(void)
{
    // L'UART0 est déjà initialisé par la console ESP-IDF.
}

void uart_send_char(char c)
{
    putchar(c);
}

void uart_send_string(const char *str)
{
    fputs(str, stdout);
}

char uart_receive_char(void)
{
    int c = getchar();

    return (c == EOF) ? '\0' : (char)c;
}

void uart_receive_string(char *buffer, size_t size)
{
    size_t i = 0;

    if (size == 0)
    {
        return;
    }

    while (i < size - 1)
    {
        char c = uart_receive_char();

        if (c == '\0')
        {
            vTaskDelay(pdMS_TO_TICKS(10));
            continue;
        }

        if (c == '\n' || c == '\r')
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
}
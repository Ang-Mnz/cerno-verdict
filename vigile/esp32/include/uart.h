#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>

void uart_init(void);
void uart_send_char(char c);
void uart_send_string(const char *str);
char uart_receive_char(void);
void uart_receive_string(char *buffer, size_t size);

#endif

/*
 * uart.h
 *
 *  Created on: 18 sept. 2026
 *      Author: angmnz
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(void);
void uart_send_char(char c);
void uart_send_string(const char *str);

char uart_receive_char(void);
void uart_receive_string(char *buffer, uint32_t size);

#endif /* UART_H_ */

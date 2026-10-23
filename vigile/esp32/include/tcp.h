#ifndef TCP_H
#define TCP_H

#include <stddef.h>

void vigile_tcp_init(void);
void vigile_tcp_receive_string(char *buffer, size_t size);

#endif
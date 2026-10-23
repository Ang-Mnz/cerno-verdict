#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stddef.h>

void communication_init(void);
void communication_receive_string(char *buffer, size_t size);

#endif
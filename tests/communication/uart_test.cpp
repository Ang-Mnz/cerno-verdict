#include <cassert>
#include <cstdint>
#include <iostream>

#include "communication/uart.hpp"

int main()
{
	Uart uart;

	// Le buffer de réception doit être vide
	uint8_t value = 0;
	assert(!uart.receive(value));

	// Injection d'une donnée reçue
	uart.inject(0x42);

	assert(uart.receive(value));
	assert(value == 0x42);

	// FIFO : plusieurs données
	uart.inject(0x10);
	uart.inject(0x20);
	uart.inject(0x30);

	assert(uart.receive(value));
	assert(value == 0x10);

	assert(uart.receive(value));
	assert(value == 0x20);

	assert(uart.receive(value));
	assert(value == 0x30);

	// Le buffer est à nouveau vide
	assert(!uart.receive(value));

	// Test de send
	assert(uart.send(0x55));

	std::cout << "Uart tests passed." << std::endl;

	return 0;
}

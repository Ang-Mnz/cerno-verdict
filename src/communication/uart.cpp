#include <iostream>

#include "uart.hpp"

Uart::Uart()
	: rx_buffer_(64)
{
}

void Uart::inject(uint8_t value)
{
	rx_buffer_.push(value);
}

bool Uart::receive(uint8_t& value)
{
	return rx_buffer_.pop(value);
}

bool Uart::send(uint8_t value)
{
	std::cout<< value << std::endl;

	return true;
}

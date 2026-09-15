#pragma once

#include <cstdint>

#include "circular_buffer.hpp"

class Uart {
	public:

		Uart();

		bool send(uint8_t value);
		bool receive(uint8_t& value);

		void inject(uint8_t value);

	private:

		CircularBuffer rx_buffer_;
};

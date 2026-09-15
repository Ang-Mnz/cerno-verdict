#pragma once

#include <cstdint>

class Register8 {
	public:

		Register8();

		void setBit(uint8_t bit);
		void clearBit(uint8_t bit);
		void toggleBit(uint8_t bit);
		bool isBitSet(uint8_t bit) const;

		uint8_t read() const;
		void write(uint8_t value);



	private:
		uint8_t value_;
};

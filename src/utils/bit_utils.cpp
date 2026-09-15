#include "bit_utils.hpp"

void setBit(uint8_t& value, uint8_t bit)
{
	uint8_t mask = 1 << bit;
	value = value | mask;
}

void clearBit(uint8_t& value, uint8_t bit)
{
	uint8_t mask = 1 << bit;
	value = value & ~mask;
}

void toggleBit(uint8_t& value, uint8_t bit)
{
	uint8_t mask = 1 << bit;
	value = value ^ mask;
}

bool isBitSet(uint8_t value, uint8_t bit)
{
	uint8_t mask = 1 << bit;
	return value & mask;
}

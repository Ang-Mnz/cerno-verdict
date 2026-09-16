#include <cassert>
#include <cstdint>
#include <iostream>

#include "utils/bit_utils.hpp"

int main()
{
	uint8_t value = 0;

	// setBit
	setBit(value, 0);
	assert(value == 0b00000001);

	setBit(value, 3);
	assert(value == 0b00001001);

	setBit(value, 7);
	assert(value == 0b10001001);


	// isBitSet
	assert(isBitSet(value, 0));
	assert(isBitSet(value, 3));
	assert(isBitSet(value, 7));

	assert(!isBitSet(value, 1));
	assert(!isBitSet(value, 6));


	// clearBit
	clearBit(value, 3);
	assert(value == 0b10000001);

	assert(!isBitSet(value, 3));


	// toggleBit
	toggleBit(value, 1);
	assert(value == 0b10000011);

	toggleBit(value, 1);
	assert(value == 0b10000001);

	toggleBit(value, 7);
	assert(value == 0b00000001);

	assert(!isBitSet(value, 7));


	std::cout << "BitUtils tests passed." << std::endl;

	return 0;
}

#include <cassert>
#include <cstdint>
#include <iostream>

#include "hardware/register8.hpp"

int main()
{
	Register8 reg;

	// Constructeur
	assert(reg.read() == 0);

	// setBit
	reg.setBit(0);
	assert(reg.read() == 0b00000001);

	reg.setBit(3);
	assert(reg.read() == 0b00001001);

	reg.setBit(7);
	assert(reg.read() == 0b10001001);

	// isBitSet
	assert(reg.isBitSet(0));
	assert(reg.isBitSet(3));
	assert(reg.isBitSet(7));

	assert(!reg.isBitSet(1));
	assert(!reg.isBitSet(6));

	// clearBit
	reg.clearBit(3);
	assert(reg.read() == 0b10000001);

	assert(!reg.isBitSet(3));

	// toggleBit
	reg.toggleBit(1);
	assert(reg.read() == 0b10000011);

	reg.toggleBit(1);
	assert(reg.read() == 0b10000001);

	reg.toggleBit(7);
	assert(reg.read() == 0b00000001);

	// write
	reg.write(0b10101010);
	assert(reg.read() == 0b10101010);

	assert(reg.isBitSet(1));
	assert(reg.isBitSet(3));
	assert(reg.isBitSet(5));
	assert(reg.isBitSet(7));

	assert(!reg.isBitSet(0));
	assert(!reg.isBitSet(2));
	assert(!reg.isBitSet(4));
	assert(!reg.isBitSet(6));

	std::cout << "Register8 tests passed." << std::endl;

	return 0;
}

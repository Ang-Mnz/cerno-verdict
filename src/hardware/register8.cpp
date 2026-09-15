#include "register8.hpp"

#include "utils/bit_utils.hpp"

Register8::Register8()
{
	this->value_ = 0;
}

void Register8::setBit(uint8_t bit)
{
	::setBit(this->value_, bit);
}

void Register8::clearBit(uint8_t bit)
{
	::clearBit(this->value_, bit);
}

void Register8::toggleBit(uint8_t bit)
{
	::toggleBit(this->value_, bit);
}

bool Register8::isBitSet(uint8_t bit) const
{
	return ::isBitSet(this->value_, bit);
}

uint8_t Register8::read() const
{
	return this->value_;
}

void Register8::write(uint8_t value)
{
	this->value_ = value;
}

#pragma once

#include <cstdint>

void setBit(uint8_t& value, uint8_t bit);
void clearBit(uint8_t& value, uint8_t bit);
void toggleBit(uint8_t& value, uint8_t bit);
bool isBitSet(uint8_t value, uint8_t bit);

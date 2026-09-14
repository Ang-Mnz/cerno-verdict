#include <cassert>
#include <cstdint>
#include <iostream>

#include "communication/circular_buffer.hpp"

int main()
{
	CircularBuffer buffer(3);

	// Buffer initialement vide
	assert(buffer.empty());
	assert(!buffer.full());
	assert(buffer.size() == 0);
	assert(buffer.capacity() == 3);

	// Ajout de données
	assert(buffer.push(10));
	assert(buffer.push(20));
	assert(buffer.push(30));

	assert(!buffer.empty());
	assert(buffer.full());
	assert(buffer.size() == 3);

	// Le buffer est plein
	assert(!buffer.push(40));

	// Lecture dans l'ordre FIFO
	uint8_t value;

	assert(buffer.pop(value));
	assert(value == 10);

	assert(buffer.pop(value));
	assert(value == 20);

	assert(buffer.size() == 1);

	// Vérification du fonctionnement circulaire
	assert(buffer.push(40));
	assert(buffer.push(50));

	assert(buffer.full());

	assert(buffer.pop(value));
	assert(value == 30);

	assert(buffer.pop(value));
	assert(value == 40);

	assert(buffer.pop(value));
	assert(value == 50);

	// Le buffer est de nouveau vide
	assert(buffer.empty());
	assert(buffer.size() == 0);

	// Impossible de lire dans un buffer vide
	assert(!buffer.pop(value));

	std::cout << "CircularBuffer tests passed." << std::endl;

	return 0;
}

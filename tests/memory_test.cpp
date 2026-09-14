#include <iostream>
#include <cassert>

#include "memory/memory.hpp"

int main()
{
	// Constructeur
	MemoryBuffer buffer1(5);

	assert(buffer1.size() == 5);

	buffer1.data()[0] = 42;

	// Constructeur par copie
	MemoryBuffer buffer2(buffer1);

	assert(buffer2.size() == 5);
	assert(buffer2.data()[0] == 42);

	// Vérification que la copie possède sa propre mémoire
	buffer2.data()[0] = 99;

	assert(buffer1.data()[0] == 42);
	assert(buffer2.data()[0] == 99);

	// Constructeur par déplacement
	MemoryBuffer buffer3(std::move(buffer1));

	assert(buffer3.size() == 5);
	assert(buffer3.data()[0] == 42);
	assert(buffer1.size() == 0);
	assert(buffer1.data() == nullptr);

	// Opérateur d'affectation par copie
	MemoryBuffer buffer4(2);

	buffer4 = buffer2;

	assert(buffer4.size() == 5);
	assert(buffer4.data()[0] == 99);

	// Opérateur d'affectation par déplacement
	MemoryBuffer buffer5(2);

	buffer5 = std::move(buffer2);

	assert(buffer5.size() == 5);
	assert(buffer5.data()[0] == 99);
	assert(buffer2.size() == 0);
	assert(buffer2.data() == nullptr);

	std::cout << "MemoryBuffer tests passed." << std::endl;

	return 0;
}

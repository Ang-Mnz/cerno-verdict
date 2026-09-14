#include <iostream>

#include "memory/memory.hpp"

int main()
{
	MemoryBuffer buffer(10);

	std::cout << "Size: " << buffer.size() << std::endl;

	return 0;
}

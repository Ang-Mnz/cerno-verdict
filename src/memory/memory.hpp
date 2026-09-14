#pragma once

#include <cstdint>
#include <cstddef>

class MemoryBuffer {
	public:

		// Constructeurs
		MemoryBuffer(std::size_t size);
		MemoryBuffer(const MemoryBuffer & other);
		MemoryBuffer(MemoryBuffer && other);

		// Destructeur
		~MemoryBuffer();

		// Opérateurs
		MemoryBuffer& operator=(const MemoryBuffer & other);
		MemoryBuffer& operator=(MemoryBuffer && other);

		// Getters
		std::size_t size() const;
		const uint8_t* data() const;
		uint8_t* data();

	private :

		uint8_t * data_;
		std::size_t size_;

};

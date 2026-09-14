#pragma once

#include <cstddef>
#include <cstdint>

class CircularBuffer {
	public:

		CircularBuffer(std::size_t capacity);
		~CircularBuffer();

		bool push(uint8_t value);
		bool pop(uint8_t& value);

		bool empty() const;
		bool full() const;
		std::size_t size() const;
		std::size_t capacity() const;

	private:

		uint8_t* data_;
		std::size_t capacity_;
		std::size_t size_;
		std::size_t read_index_;
		std::size_t write_index_;
};

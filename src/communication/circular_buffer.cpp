#include "circular_buffer.hpp"

CircularBuffer::CircularBuffer(std::size_t capacity)
	: capacity_(capacity),
	  size_(0),
	  read_index_(0),
	  write_index_(0)
{
	data_ = new uint8_t[capacity_];
}

CircularBuffer::~CircularBuffer()
{
	delete[] data_;
}

bool CircularBuffer::push(uint8_t value)
{
	if (full())
		return false;

	data_[write_index_] = value;

	write_index_++;

	if (write_index_ == capacity_)
		write_index_ = 0;

	size_++;

	return true;
}

bool CircularBuffer::pop(uint8_t& value)
{
	if (empty())
		return false;

	value = data_[read_index_];

	read_index_++;

	if (read_index_ == capacity_)
		read_index_ = 0;

	size_--;

	return true;
}

bool CircularBuffer::empty() const
{
	return size_ == 0;
}

bool CircularBuffer::full() const
{
	return size_ == capacity_;
}

std::size_t CircularBuffer::size() const
{
	return size_;
}

std::size_t CircularBuffer::capacity() const
{
	return capacity_;
}

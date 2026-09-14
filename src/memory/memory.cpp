#include "memory.hpp"

MemoryBuffer::MemoryBuffer(std::size_t size) : size_(size) {
	this->data_ = new uint8_t[size];

	for(std::size_t i = 0; i < size_; i++) {
		this->data_[i] = 0;
	}
}

MemoryBuffer::MemoryBuffer(const MemoryBuffer & other) : size_(other.size_) {
	this->data_ = new uint8_t[size_];

	for(std::size_t i = 0; i < other.size_; i++) {
		this->data_[i] = other.data_[i];
	}
}

MemoryBuffer::MemoryBuffer(MemoryBuffer && other) : size_(other.size_), data_(other.data_) {
	other.size_ = 0;
	other.data_ = nullptr;
}

MemoryBuffer::~MemoryBuffer() {
	delete [] data_;
}

MemoryBuffer& MemoryBuffer::operator=(const MemoryBuffer & other) {

	if (this == &other)
		return *this;

	delete [] this->data_;

	this->size_ = other.size_;
	this->data_ = new uint8_t[size_];

	for(std::size_t i = 0; i < other.size_; i++) {
		this->data_[i] = other.data_[i];
	}

	return *this;
}

MemoryBuffer& MemoryBuffer::operator=(MemoryBuffer && other) {

	if (this == &other)
		return *this;

	delete [] this->data_;

	this->size_ = other.size_;
	this->data_ = other.data_;

	other.size_ = 0;
	other.data_ = nullptr;

	return *this;
}

std::size_t MemoryBuffer::size() const {
	return this->size_;
}

const uint8_t* MemoryBuffer::data() const {
	return this->data_;
}

uint8_t* MemoryBuffer::data() {
	return this->data_;
}

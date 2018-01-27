#include <iostream>

#include "memPool.h"

MemPool& MemPool::getInstance() {
	// Instantiated on the first use
	// Guaranteed to be destroyed
	static MemPool instance;
	return instance;
}

MemPool::MemPool() { }

MemPool::~MemPool() {
	free(_memory_pool);
}

void MemPool::initialize(size_t size) {
	_memory_size = size;
	_current_ptr = 0;

	// Using malloc instead of new in order to prevent circular dependecies
	_memory_pool = (char*) malloc(_memory_size);
}

char* MemPool::allocateBlock(size_t size) {
	if (_current_ptr + size > _memory_size) {
		// If no memory is left in the memory pool
		return nullptr;
	}

	size_t before_allocation_ptr = _current_ptr;
	_current_ptr += size;

	// returns a block of the requested size from the array
	return (_memory_pool + before_allocation_ptr);
}
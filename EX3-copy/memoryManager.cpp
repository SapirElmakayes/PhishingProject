#include <iostream>
#include <math.h>

#include "memoryManager.h"

MemoryManager::MemoryManager() {
}

MemoryManager::~MemoryManager() {
}

void MemoryManager::initialize(size_t memorySize) {
	_size = memorySize;

	MemPool& memory_pool = MemPool::getInstance();

	// Allocating the memory pool
	memory_pool.initialize(_size);
}

void* MemoryManager::allocate(size_t size) {
	std::cout << "Starting allocation original size " << size << std::endl;
	size_t real_size = getRealSize(size);
	int power = (int) log2(real_size);

	std::cout << "Allocting real size: " << real_size << std::endl;

	MemPool& memory_pool = MemPool::getInstance();

	void* allocated_memory = allocateMemoryInternal(memory_pool, real_size, power);
	if (!allocated_memory) {
		// If failed to allocate memory
		return nullptr;
	}

	// Skip the memory header
	return reinterpret_cast<char*>(allocated_memory) + sizeof(FreeListNode);
}

void MemoryManager::free(void* ptr) {
	std::cout << "freeing ptr" << std::endl;
	void* header_ptr = reinterpret_cast<char*>(ptr) - sizeof(FreeListNode);
	FreeListNode* memory_header = reinterpret_cast<FreeListNode*>(header_ptr);

	std::cout << "cast header successfuly" << std::endl;

	// Finds the free list segment
	size_t allocation_size = memory_header->size;
	int power = (int) log2(allocation_size);
	if (power > UPPER_BOUND_ALLOCTION_BYTES) {
		power = UPPER_BOUND_ALLOCTION_BYTES;
	}

	_freeList[power].append(memory_header);
}

void* MemoryManager::allocateMemoryInternal(MemPool& memory_pool, size_t real_size, int power) {
	if (power > UPPER_BOUND_ALLOCTION_BYTES) {
		// If the allocation is of bigger size than the upper bound of the free-list
		power = UPPER_BOUND_ALLOCTION_BYTES;
	}

	std::cout << "real power: " << power << std::endl;

	// If the allocation is of normal size
	return allocatedSegmentedFreeListMemory(memory_pool, real_size, power);
}

void* MemoryManager::allocatedSegmentedFreeListMemory(MemPool& memory_pool, size_t real_size, int power) {
	void *allocated_block = tryGetBlockFromFreeList(power, real_size);
	if (allocated_block) {
		std::cout << "found memory from free list" << std::endl;
		return allocated_block;
	}

	return tryGetBlockFromMemoryPool(memory_pool, real_size);
}

void* MemoryManager::tryGetBlockFromFreeList(int power, size_t real_size) {
	if (_freeList[power].empty()) {
		std::cout << "free-list is empty" << std::endl;
		return nullptr;
	}

	std::cout << "Looking inside the free-list" << std::endl;
	return _freeList[power].remove(real_size);
}

void* MemoryManager::tryGetBlockFromMemoryPool(MemPool& memory_pool, size_t real_size) {
	std::cout << "allocating memory from the array" << std::endl;

	// allocating memory for both data and memory header
	char *allocated_block = memory_pool.allocateBlock(real_size + sizeof(FreeListNode));
	if (!allocated_block) {
		// If no memory left in the memory pool
		return nullptr;
	}

	// Setting the allocated block header
	FreeListNode* allocated_block_header = reinterpret_cast<FreeListNode*>(allocated_block);
	allocated_block_header->size = real_size;
	allocated_block_header->next = nullptr;

	return reinterpret_cast<void*>(allocated_block);
}

size_t MemoryManager::getRealSize(size_t size) {
	int real_number = 1;
	while (real_number < size) {
		real_number *= 2;
	}

	return real_number;
}
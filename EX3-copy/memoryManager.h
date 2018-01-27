#pragma once

#include "FreeList.h"
#include "memPool.h"

class MemoryManager {
public:
	MemoryManager();
	virtual ~MemoryManager();

	void initialize(size_t memorySize);

	void* allocate(size_t size);
	void free(void* ptr);
private:
	void* allocateMemoryInternal(MemPool& memory_pool, size_t real_size, int power);
	void* allocatedSegmentedFreeListMemory(MemPool& memory_pool, size_t real_size, int power);
	void* tryGetBlockFromFreeList(int power, size_t real_size);
	void* tryGetBlockFromMemoryPool(MemPool& memory_pool, size_t real_size);

	size_t getRealSize(size_t size);

	const static size_t UPPER_BOUND_ALLOCTION_BYTES = 10;
	size_t _size;

	// The free list is structed as follows:
	// 1 byte
	// 2 bytes
	// 4 bytes
	// ...
	// 512 bytes
	// > 512 bytes (For big size allocations)
	FreeList _freeList[UPPER_BOUND_ALLOCTION_BYTES + 1];
};
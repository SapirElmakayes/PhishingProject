#pragma once

class MemPool {
public:
	static MemPool& getInstance();
	virtual	~MemPool();

	char* allocateBlock(size_t size);
	void initialize(size_t size);
private:
	MemPool();
	
	size_t _memory_size;
	size_t _current_ptr;
	char* _memory_pool;
};
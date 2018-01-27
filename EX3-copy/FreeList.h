#pragma once

#include "FreeListNode.h"

class FreeList {
public:
	FreeList();
	
	bool empty();
	void append(FreeListNode *node);
	FreeListNode* remove(size_t size);
	
private:
	FreeListNode* _next;
};
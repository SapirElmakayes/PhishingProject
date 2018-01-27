#pragma once

#include <iostream>

struct FreeListNode {
public:
	size_t size;
	FreeListNode *next;
};
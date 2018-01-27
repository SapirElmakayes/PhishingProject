#include "FreeList.h"

FreeList::FreeList()
	: _next(nullptr) {
}

bool FreeList::empty() {
	return _next == nullptr;
}

void FreeList::append(FreeListNode *node) {
	std::cout << "appeding size " << node->size << std::endl;
	// Appending the new FreeListNode to the begining of the free list
	node->next = _next;
	_next = node;
}

// Get a node from the free list in O(1)
// When the free list is of big sizes it might take O(n)
FreeListNode* FreeList::remove(size_t size) {
	FreeListNode *runner = _next;
	FreeListNode *prev_runner = nullptr;

	// When it is a normal size allocation we will skip this loop
	while (runner && runner->size != size) {
		prev_runner = runner;
		runner = runner->next;
	}

	if (empty() || !runner) {
		std::cout << "didnt found a runner" << std::endl;
		// If no blocks appears in the free-list that matches the requested size
		return nullptr;
	}

	// Saving the found block
	FreeListNode *free_block = runner;

	if (prev_runner) {
		// If the found element is in the middle of the linked list
		// connecting the previous element to its next sibling
		prev_runner->next = runner->next;
	} else {
		// If the found element is the first element
		// setting is next sibling to be the first element
		_next = runner->next;
	}

	// reseting the next value of the deleted block
	free_block->next = nullptr;

	// Returning the fist block
	return free_block;
}
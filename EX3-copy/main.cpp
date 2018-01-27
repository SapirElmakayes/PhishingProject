#include <iostream>
#include <string.h>
#include "memoryManager.h"

#define SIZE_FLAG "-S"
#define SIZE_FLAG_INDEX 1
#define SIZE_FLAG_VALUE_INDEX 2
#define NUM_OF_ARGUMENTS 3

#define EXIT_ERROR_ALLOCATION 1
#define EXIT_ERROR_ARGS 2

// A global memory manager to the whole program
MemoryManager gMemoryManager;

class Test {
public:
	Test(int a) {
		_a = a;
		t = 'a';
		std::cout << _a << std::endl;
		std::cout << t << std::endl;
	}
private:
	int _a;
	char t;
};

int main(int argc, char* argv[]) {
	if (argc != NUM_OF_ARGUMENTS) {
		std::cout << "Error: -S size [size of heap in bytes] is missing" << std::endl;
		return EXIT_ERROR_ARGS;
	}

	if (strcmp(argv[SIZE_FLAG_INDEX], SIZE_FLAG) != 0) {
		std::cout << "Error: " << argv[SIZE_FLAG_INDEX] << " command is not supported" << std::endl;
		return EXIT_ERROR_ARGS;
	}

	int buffer_size_in_bytes = std::stoi(argv[SIZE_FLAG_VALUE_INDEX]);

	gMemoryManager.initialize(buffer_size_in_bytes);

	// Test *t = new Test(6);
	// delete t;

	// Test *t2 = new Test(5);

	// int* a = new int[512 / 4];
	// if (a == nullptr) {
	// 	std::cout << "Failed to allocate" << std::endl;
	// 	return 1;
	// }

	// std::cout << "====" << std::endl;

	// delete a;

	// std::cout << "====" << std::endl;

	// int* b = new int[1];

	// std::cout << "====" << std::endl;

	// int* c = new int[1];

	// std::cout << "====" << std::endl;

	return 0;
}

// Overloading new and delete
void* operator new (size_t size)  {
	return gMemoryManager.allocate(size);
}
 
void* operator new[] (size_t size) {
	return gMemoryManager.allocate(size);
}
 
void operator delete (void* pointerToDelete) {
	gMemoryManager.free(pointerToDelete);
}
 
void operator delete[ ] (void* arrayToDelete) {
	gMemoryManager.free(arrayToDelete);
}
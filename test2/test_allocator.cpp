#include "../Allocator/Allocator.h"
#include <iostream>
#include <thread>
#include <vector>

void testHeapBlocks() {
    Allocator allocatorHeapBlocks(100);
    for (int i = 0; i < 1000; ++i) {
        void* memory = allocatorHeapBlocks.Allocate(100);
        allocatorHeapBlocks.Deallocate(memory);
    }
    std::cout << "Heap Blocks Test Completed." << std::endl;
}

void testHeapPool() {
    Allocator allocatorHeapPool(100, 20);
    for (int i = 0; i < 1000; ++i) {
        void* memory = allocatorHeapPool.Allocate(100);
        allocatorHeapPool.Deallocate(memory);
    }
    std::cout << "Heap Pool Test Completed." << std::endl;
}

void testStaticPool() {
    char staticMemoryPool[100 * 20];
    Allocator allocatorStaticPool(100, 20, staticMemoryPool);
    for (int i = 0; i < 1000; ++i) {
        void* memory = allocatorStaticPool.Allocate(100);
        allocatorStaticPool.Deallocate(memory);
    }
    std::cout << "Static Pool Test Completed." << std::endl;
}

void testBoundaryAllocation() {
    Allocator allocator(100, 10); // Пул с 10 блоками
    void* memoryBlocks[11];

    // Попробуем выделить 11 блоков, хотя доступно только 10
    for (int i = 0; i < 11; ++i) {
        memoryBlocks[i] = allocator.Allocate(100);
        if (!memoryBlocks[i]) {
            std::cout << "Allocation failed at attempt " << i + 1 << std::endl;
            break;
        }
    }

    // Освободим память
    for (int i = 0; i < 11; ++i) {
        if (memoryBlocks[i]) {
            allocator.Deallocate(memoryBlocks[i]);
        }
    }
}

void allocateAndDeallocate(Allocator& allocator) {
    for (int i = 0; i < 100; ++i) {
        void* memory = allocator.Allocate(100);
        allocator.Deallocate(memory);
    }
}



void testMemoryLeak() {
    Allocator allocator(100);
    for (int i = 0; i < 1000; ++i) {
        allocator.Allocate(100); // Не освобождаем память
    }
    std::cout << "Memory Leak Test Completed." << std::endl;
}

void testDifferentBlockSizes() {
    Allocator smallBlocksAllocator(50);
    Allocator largeBlocksAllocator(500);

    for (int i = 0; i < 100; ++i) {
        void* smallBlock = smallBlocksAllocator.Allocate(100);
        void* largeBlock = largeBlocksAllocator.Allocate(100);
        smallBlocksAllocator.Deallocate(smallBlock);
        largeBlocksAllocator.Deallocate(largeBlock);
    }
    std::cout << "Different Block Sizes Test Completed." << std::endl;
}

class MyClass {
public:
    int data;
    MyClass() : data(0) {}
};

void testCustomType() {
    AllocatorPool<MyClass, 20> allocator;
    for (int i = 0; i < 20; ++i) {
// Выделяем память и приводим указатель к типу MyClass*
        MyClass* obj = static_cast<MyClass*>(allocator.Allocate(100));        obj->data = i;
        allocator.Deallocate(obj);
    }
    std::cout << "Custom Type Test Completed." << std::endl;
}

int main() {
    testHeapBlocks();
    testHeapPool();
    testStaticPool();
    testBoundaryAllocation();
    testMemoryLeak();
    testDifferentBlockSizes();
    testCustomType();
    return 0;
}

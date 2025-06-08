#include "include/thread.hpp"
#include "include/scheduler.hpp"
#include <iostream>
#include <vector>
#include <memory>

// Let's define a simple type for a thread ID
using ThreadId = uint32_t;

// Global counter for assigning unique thread IDs
static ThreadId nextThreadId = 1;

// In a real kernel, the stack would be allocated from memory.
// For our conceptual model, we can simulate this.
static constexpr size_t STACK_SIZE = 4096; // Example stack size

// A simple way to represent a thread's stack
using Stack = std::vector<uint8_t>;

// Function to conceptually allocate a stack
static std::unique_ptr<Stack> allocateStack() {
    return std::make_unique<Stack>(STACK_SIZE);
}

extern Scheduler kernelScheduler;

// The scheduler will hold pointers to these.
static std::vector<ThreadControlBlock> all_tcbs;


// Function to create a new thread
ThreadId create_thread(std::function<void()> entryPoint, int priority) {
    ThreadId newId = nextThreadId++;

    // 1. Allocate a stack (conceptually)
    // For simplicity, we just simulate allocation; the stack object's lifetime
    // needs to be managed if we were doing actual context switching.
    auto stack = allocateStack();
    uintptr_t stackTop = reinterpret_cast<uintptr_t>(stack->data() + stack->size());
    // In a real system, stackTop would be the initial stack pointer.

    // 2. Create and initialize a TCB
    // Create TCB directly in the global vector to manage its lifetime
    all_tcbs.emplace_back(newId, entryPoint, priority);
    ThreadControlBlock& newThread = all_tcbs.back(); // Get a reference to the newly added TCB
    newThread.stackPointer = stackTop; // Store the (conceptual) stack pointer
    newThread.state = ThreadState::READY;

    // 3. Add the new thread to the scheduler's ready queue
    kernelScheduler.add_thread(newThread);

    std::cout << "Thread created with ID: " << newId << " and priority: " << priority << std::endl;

    return newId;
}
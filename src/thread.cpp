#include "../include/thread.hpp"
#include "../include/scheduler.hpp"
#include <iostream>
#include <vector>
#include <memory>

// Define a simple type for thread ID
using ThreadId = uint32_t;

// Global counter for assigning unique thread IDs
static ThreadId nextThreadId = 1;

// Simulating the stack from memory
static constexpr size_t STACK_SIZE = 4096; 

// Thread's stack
using Stack = std::vector<uint8_t>;

// Function to conceptually allocate a stack
static std::unique_ptr<Stack> allocateStack(){
    return std::make_unique<Stack>(STACK_SIZE);
}

// Declare a global scheduler instance. It will be defined in kernel.cpp
extern Scheduler kernelScheduler;

// Thread list before we have a scheduler
static std::vector<ThreadControlBlock> threads;

// Function to create a new thread
ThreadId createThread(std::function<void()> entryPoint, int priority){
    ThreadId newId = nextThreadId++;

    // Allocate stack
    auto stack = allocateStack();
    uintptr_t stackTop = reinterpret_cast<uintptr_t>(stack->data() + stack->size());

    // Create and initialize the TCB
    all_tcbs.emplace_back(newId, entryPoint, priority);
    ThreadControlBlock newThread(newId, entryPoint, priority);
    newThread.stackPointer = stackTop;
    newThread.state = ThreadState::READY;

    // Add the new thread to scheduler's ready queue
    kernelScheduler.add_thread(newThread);

    std::cout << "Thread created with ID: " << newId << " and priority: " << priority << std::endl;

    return newId;
}
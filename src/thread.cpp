#include "../include/thread.hpp"
#include <iostream>
#include <vector>
#include <memory>

// simple thread id
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

// Thread list before we have a scheduler
static std::vector<ThreadControlBlock> threads;

// Function to create a new thread
ThreadId createThread(std::function<void()> entryPoint, int priority){
    ThreadId newId = nextThreadId++;

    // Allocate stack
    auto stack = allocateStack();
    uintptr_t stackTop = reinterpret_cast<uintptr_t>(stack->data() + stack->size());

    // Create and initialize the TCB
    ThreadControlBlock newThread(newId, entryPoint, priority);
    newThread.stackPointer = stackTop;
    newThread.state = ThreadState::READY;

    // Add the new thread to the list until we have a scheduler
    threads.push_back(newThread);

    std::cout << "Thread created with ID: " << newId << " and priority: " << priority << std::endl;

    return newId;
}

// For now, a single function to list all created threads
void list_threads(){
    std::cout << "--------List of Threads--------" << std::endl;
    for(const auto& thread : threads){
        std::cout << "Thread ID: " << thread.threadId << ", Priority: " << thread.priority 
                    << ", State: ";
        switch (thread.state)
        {
        case Threadstate::READY:
            std::cout << "READY" << std::endl;
            break;
        case Threadstate::RUNNING:
            std::cout << "RUNNING" << std::endl;
            break;
        case Threadstate::BLOCKED:
            std::cout << "BLOCKED" << std::endl;
            break;
        case Threadstate::FINISHED:
            std::cout << "FINISHED" << std::endl;
            break;
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
} 
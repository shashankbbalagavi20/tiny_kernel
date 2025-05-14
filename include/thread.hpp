#ifndef THREAD_HPP
#define THREAD_HPP

#include <cstdint>
#include <functional>
#include <vector>

// Forward declaration
class Mutex;
class Semaphore;

enum class ThreadState {
    READY,
    RUNNING,
    BLOCKED,
    FINISHED
};

struct ThreadControlBlock
{
    unit32_t threadID; // Unique identifier for the thread
    uintptr_t stackPointer; // Pointer to current top of stack
    std::function<void()> programCounter; // Function the thread will execute
    ThreadState state; // Current state of the thread
    int priority; // Thread priority

    std::vector<Mutex*> heldMutexex; // Mutexes held by this thread
    std::vector<Semaphore*> heldSemaphores; // Semaphores held by this thread

    // Constructor
    ThreadControlBlock(unit32_t id, std::function<void()> entry,
     int prio) : threadID(id), programCounter(entry), priority(prio), state(ThreadState::READY), stackPointer(0) {}
};

#endif // THREAD_HPP
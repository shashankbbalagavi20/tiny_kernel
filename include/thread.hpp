#ifndef THREAD_HPP
#define THREAD_HPP

#include <cstdint>
#include <functional>
#include <vector>

using ThreadId = uint32_t;

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
    uint32_t threadId; // Unique identifier for the thread
    uintptr_t stackPointer; // Pointer to current top of stack
    std::function<void()> programCounter; // Function the thread will execute
    ThreadState state; // Current state of the thread

    std::vector<Mutex*> heldMutexes; // Mutexes held by this thread
    std::vector<Semaphore*> heldSemaphores; // Semaphores held by this thread

    int get_priority() const {
        return priority;
    }
    // Constructor
    ThreadControlBlock(uint32_t id, std::function<void()> entry,
     int prio) : threadId(id), stackPointer(0), programCounter(entry), state(ThreadState::READY), heldMutexes(), heldSemaphores(), priority(prio) {}
   
    private:
    int priority;
};

// Global  function to create a thread
ThreadId create_thread(std::function<void()> entryPoint, int priority);
#endif // THREAD_HPP
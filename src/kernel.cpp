#include "include/scheduler.hpp"
#include "include/thread.hpp"
#include <iostream>
#include <chrono>
#include <thread>

// Define the global scheduler instance
Scheduler kernelScheduler;

// A simple function for our threads
void thread_function_one() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 (Priority: 5) running iteration " << i << std::endl;
        // For now, simulate some work.
    }
    std::cout << "Thread 1 (Priority: 5) finished." << std::endl;
    // In a real scenario, this thread would then be marked FINISHED and removed from scheduler.
}

void thread_function_two() {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Thread 2 (Priority: 10) running iteration " << i << std::endl;
    }
    std::cout << "Thread 2 (Priority: 10) finished." << std::endl;
}

// The main kernel entry point
int main() {
    std::cout << "Tiny Kernel starting..." << std::endl;

    // Create some threads
    create_thread(thread_function_one, 5);  // Lower priority
    create_thread(thread_function_two, 10); // Higher priority

    std::cout << "Threads created. Starting scheduling loop." << std::endl;

    // Main scheduling loop (conceptual)
    // This loop simulates the kernel continuously picking and running threads.
    while (true) {
        ThreadControlBlock* nextThread = kernelScheduler.get_next_thread();

        if (nextThread) {
            // Simulate running the thread's function
            // In a real kernel, this is where context switch happens.
            // For now, we're directly calling the function.
            std::cout << "Kernel: Dispatching Thread " << nextThread->threadId << std::endl;
            nextThread->programCounter(); // Execute the thread's entry point function
            nextThread->state = ThreadState::FINISHED; // Mark as finished after execution
            // In a real scenario, a thread would yield or block, and then be re-added
            // if it's not finished. This is a very simplified run-to-completion model.
        } else {
            std::cout << "Kernel: No ready threads. All done or waiting." << std::endl;
            break; // Exit if no more threads to run
        }

        // Simulate a time slice or interrupt by re-scheduling
        // For now, we're letting threads run to completion within their function call.
        // Later, we'll introduce preemption and context switching.
    }

    std::cout << "Tiny Kernel finished." << std::endl;

    return 0;
}
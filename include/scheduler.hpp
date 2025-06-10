#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <queue>
#include "thread.hpp"

class Scheduler {
public:
    Scheduler();

    void add_thread(ThreadControlBlock& thread);
    ThreadControlBlock* get_next_thread();
    void remove_thread(ThreadControlBlock* thread);

private:
    // Comparator for the priority queue (higher priority gets higher precedence)
    struct ComparePriority {
        bool operator()(const ThreadControlBlock* a, const ThreadControlBlock* b){
            return a->get_priority() < b->get_priority();
        }
    };
    // Ready queue
    std::priority_queue<ThreadControlBlock*, std::vector<ThreadControlBlock*>, ComparePriority> readyQueue;

    // Currently running thread (nullptr if none)
    ThreadControlBlock* currentThread;
};

#endif // SCHEDULER_HPP
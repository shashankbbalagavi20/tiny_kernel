#include "scheduler.hpp"
#include "thread.hpp"
#include <iostream>
#include <algorithm>

Scheduler::Scheduler() : currentThread(nullptr) {}

void Scheduler::add_thread(ThreadControlBlock& thread){
    readyQueue.push(&thread);
    std::cout << "Thread " << thread.threadId << "added to the queue." << std::endl;
}

ThreadControlBlock* Scheduler::get_next_thread(){
    if(!readyQueue.empty()){
        currentThread = readyQueue.top();
        readyQueue.pop();
        currentThread->state = ThreadState::RUNNING;
        std::cout << "Next Thread to run: " << currentThread->threadId << "(Priority: " << currentThread->get_priority() << ")" << std::endl;
        return currentThread;
    }
    return nullptr; // No threads available
}

void Scheduler::remove_thread(ThreadControlBlock* thread){
    // Since it is a priority queue, direct removal is not supported.
    // A more robust implementation might involve a separate list or marking for removal.
    // For this conceptual model, we can simulate removal by creating a new queue
    std::priority_queue<ThreadControlBlock*, std::vector<ThreadControlBlock*>, ComparePriority> tempQueue;
    bool found = false;
    while(!readyQueue.empty()){
        ThreadControlBlock* current = readyQueue.top();
        readyQueue.pop();
        if(current->threadId != thread->threadId || found){
            tempQueue.push(current);
        }
        else{
            std::cout << "Thread " << thread->threadId << " removed from the queue." << std::endl;
            found = true;
        }
    }
    readyQueue = tempQueue;
    if(currentThread && currentThread->threadId == thread->threadId){
        currentThread = nullptr;
    }
}
# Tiny Kernel: Preemptive Priority-Based Thread Scheduler (Conceptual C++)

## Project Overview

This project implements a conceptual preemptive priority-based thread scheduler in C++, simulating fundamental operating system concepts. The goal is to build a basic understanding of thread management, scheduling algorithms, and inter-thread synchronization within a simplified kernel environment.

---

## Current Status

As of this README, the core thread management and priority-based scheduling mechanisms are in place.

### Implemented Features:

* **Thread Control Block (TCB):** Defined a `ThreadControlBlock` structure (`include/thread.hpp`) to encapsulate thread-specific state, including a unique ID, conceptual stack pointer, program counter (function entry point), current state, and priority. Encapsulation for priority is achieved via a `get_priority()` method.
* **Thread Creation:** A `create_thread()` function (`src/thread.cpp`) handles the conceptual allocation of thread stacks, initialization of TCBs, and adding new threads to the scheduler's ready queue.
* **Priority-Based Scheduler:** A `Scheduler` class (`include/scheduler.hpp`, `src/scheduler.cpp`) manages the ready queue using a `std::priority_queue`. It's capable of selecting the highest-priority ready thread for execution.
* **Basic Kernel Loop:** The `main()` function in `src/kernel.cpp` acts as the kernel's entry point, demonstrating thread creation and a continuous scheduling loop that dispatches threads based on their priority.
* **Modular Design:** The project is structured with clear separation of concerns into `thread`, `scheduler`, and future `sync` modules, using dedicated header (`.hpp`) and source (`.cpp`) files.
* **Version Control:** The project is managed using Git, tracking changes and facilitating collaborative development.

---

## How to Build and Run

This project uses `g++` for compilation, without relying on build systems like Make or CMake.

### Prerequisites:

* A **C++17 compatible compiler** (e.g., `g++`). If you're on Windows, ensure you have Git Bash with MinGW (or similar) installed.

### Steps:

1.  **Navigate to the project root directory:**
    Open your terminal (e.g., Git Bash on Windows) and change directory to the `tiny_kernel` folder.

2.  **Compile the source code:**
    Execute the following command to compile all source files and create the executable:

    ```bash
    g++ -std=c++17 -Wall -Wextra -g -Iinclude src/thread.cpp src/scheduler.cpp src/kernel.cpp -o tiny_kernel.exe
    ```

    * `-std=c++17`: Specifies the C++17 standard.
    * `-Wall -Wextra`: Enables extensive compiler warnings (highly recommended).
    * `-g`: Includes debugging information.
    * `-Iinclude`: Tells the compiler to look for header files in the `include/` directory.
    * `-o tiny_kernel.exe`: Specifies the output executable name for Windows.

3.  **Run the executable:**
    After successful compilation, run the kernel simulation:

    ```bash
    ./tiny_kernel.exe
    ```

### Expected Output:

The output will demonstrate the priority-based scheduling. Higher priority threads (e.g., priority 10) will run to completion before lower priority threads (e.g., priority 5), even if created in a different order. The program will terminate once all created threads have completed their execution.

---

## Next Steps / Future Plan

The following features are planned to enhance the kernel's capabilities and realism:

1.  **Conceptual Context Switching:** Implement a simulated mechanism to save and restore the "CPU context" (e.g., conceptual register set) for threads, enabling true multitasking by allowing the kernel to pause and resume threads.
2.  **Preemptive Scheduling (Time Slicing):** Introduce a mechanism to simulate timer interrupts, forcing the scheduler to regain control and perform a context switch after a defined time slice, even if a thread hasn't finished its execution.
3.  **Synchronization Primitives:**
    * **Mutex:** Implement `Mutex` with `lock()` and `unlock()` operations to protect shared resources, handling thread blocking and waking.
    * **Semaphore:** Implement `Semaphore` with `acquire()` and `release()` operations for more general signaling and resource counting.
4.  **Thread State Management:** Refine thread state transitions (`READY`, `RUNNING`, `BLOCKED`, `FINISHED`) and implement functions like `yield_thread()`, `block_thread()`, and `unblock_thread()` to allow threads to voluntarily yield control or wait for resources.
5.  **Thread Termination:** Improve handling of finished threads by formally removing them from the scheduler and releasing any associated resources.# Tiny Kernel: Preemptive Priority-Based Thread Scheduler (Conceptual C++)

## Project Overview

This project implements a conceptual preemptive priority-based thread scheduler in C++, simulating fundamental operating system concepts. The goal is to build a basic understanding of thread management, scheduling algorithms, and inter-thread synchronization within a simplified kernel environment.

---

## Current Status

As of this README, the core thread management and priority-based scheduling mechanisms are in place.

### Implemented Features:

* **Thread Control Block (TCB):** Defined a `ThreadControlBlock` structure (`include/thread.hpp`) to encapsulate thread-specific state, including a unique ID, conceptual stack pointer, program counter (function entry point), current state, and priority. Encapsulation for priority is achieved via a `get_priority()` method.
* **Thread Creation:** A `create_thread()` function (`src/thread.cpp`) handles the conceptual allocation of thread stacks, initialization of TCBs, and adding new threads to the scheduler's ready queue.
* **Priority-Based Scheduler:** A `Scheduler` class (`include/scheduler.hpp`, `src/scheduler.cpp`) manages the ready queue using a `std::priority_queue`. It's capable of selecting the highest-priority ready thread for execution.
* **Basic Kernel Loop:** The `main()` function in `src/kernel.cpp` acts as the kernel's entry point, demonstrating thread creation and a continuous scheduling loop that dispatches threads based on their priority.
* **Modular Design:** The project is structured with clear separation of concerns into `thread`, `scheduler`, and future `sync` modules, using dedicated header (`.hpp`) and source (`.cpp`) files.
* **Version Control:** The project is managed using Git, tracking changes and facilitating collaborative development.

---

## How to Build and Run

This project uses `g++` for compilation, without relying on build systems like Make or CMake.

### Prerequisites:

* A **C++17 compatible compiler** (e.g., `g++`). If you're on Windows, ensure you have Git Bash with MinGW (or similar) installed.

### Steps:

1.  **Navigate to the project root directory:**
    Open your terminal (e.g., Git Bash on Windows) and change directory to the `tiny_kernel` folder.

2.  **Compile the source code:**
    Execute the following command to compile all source files and create the executable:

    ```bash
    g++ -std=c++17 -Wall -Wextra -g -Iinclude src/thread.cpp src/scheduler.cpp src/kernel.cpp -o tiny_kernel.exe
    ```

    * `-std=c++17`: Specifies the C++17 standard.
    * `-Wall -Wextra`: Enables extensive compiler warnings (highly recommended).
    * `-g`: Includes debugging information.
    * `-Iinclude`: Tells the compiler to look for header files in the `include/` directory.
    * `-o tiny_kernel.exe`: Specifies the output executable name for Windows.

3.  **Run the executable:**
    After successful compilation, run the kernel simulation:

    ```bash
    ./tiny_kernel.exe
    ```

### Expected Output:

The output will demonstrate the priority-based scheduling. Higher priority threads (e.g., priority 10) will run to completion before lower priority threads (e.g., priority 5), even if created in a different order. The program will terminate once all created threads have completed their execution.

---

## Next Steps / Future Plan

The following features are planned to enhance the kernel's capabilities and realism:

1.  **Conceptual Context Switching:** Implement a simulated mechanism to save and restore the "CPU context" (e.g., conceptual register set) for threads, enabling true multitasking by allowing the kernel to pause and resume threads.
2.  **Preemptive Scheduling (Time Slicing):** Introduce a mechanism to simulate timer interrupts, forcing the scheduler to regain control and perform a context switch after a defined time slice, even if a thread hasn't finished its execution.
3.  **Synchronization Primitives:**
    * **Mutex:** Implement `Mutex` with `lock()` and `unlock()` operations to protect shared resources, handling thread blocking and waking.
    * **Semaphore:** Implement `Semaphore` with `acquire()` and `release()` operations for more general signaling and resource counting.
4.  **Thread State Management:** Refine thread state transitions (`READY`, `RUNNING`, `BLOCKED`, `FINISHED`) and implement functions like `yield_thread()`, `block_thread()`, and `unblock_thread()` to allow threads to voluntarily yield control or wait for resources.
5.  **Thread Termination:** Improve handling of finished threads by formally removing them from the scheduler and releasing any associated resources.
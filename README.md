# Philosophers

*This project has been created as part of the 42 curriculum by eonen.*

---

## Description
A C project solving the classic **Dining Philosophers Problem** to master multithreading and thread synchronization. The simulation runs each philosopher as an independent POSIX thread (`pthread`) and represents shared forks using mutexes. 

It features a dedicated monitor thread to safely track the global state and employs an asymmetric fork pickup strategy (even/odd IDs) for deadlock prevention, alongside a custom precise sleep implementation to completely avoid data races, starvation, and memory leaks.

---

## Features & Goals
* **Synchronization:** Protecting shared state and avoiding data races using dedicated mutexes (`meal_mutex`, `print_mutex`, `death_mutex`).
* **Deadlock Prevention:** Eliminating circular wait conditions via asymmetric fork-grabbing logic.
* **Precision Timing:** Custom `precise_sleep` mechanism to ensure accurate timestamps without CPU throttling or drifting.

---

## Instructions

### Compilation & Management
```bash
make        # Compile the project and generate 'philo'
make clean  # Remove object files (.o)
make fclean # Remove object files and the executable
make re     # Recompile the entire project from scratch
```
---

## Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

./philo 5 800 200 200     # Basic simulation (5 philosophers)
./philo 5 800 200 200 10  # Simulation ends after everyone eats at least 10 times
```

--- 

## Resources
POSIX Threads & Mutexes: Linux pthreads Man Page | pthread_create | pthread_mutex

Timing & Theory: gettimeofday(2) | Dining Philosophers Problem (Wikipedia)

Debugging Tools: Valgrind Documentation

---

## AI Usage 

AI tools were utilized strictly for conceptual guidance on threading, analyzing mutex edge cases, refining the synchronization strategy, and reviewing the markdown structure. All architectural decisions, testing, and source code development were executed manually.

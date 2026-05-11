*This project has been created as part of the 42 curriculum by eonen.*

# Philosophers

## Description

The **Philosophers** project is a concurrency and synchronization project from the 42 curriculum inspired by the classic **Dining Philosophers Problem**.

The objective of the project is to simulate philosophers sitting around a table while following strict timing and synchronization rules. Each philosopher alternates between:

- eating
- sleeping
- thinking

To eat, a philosopher must acquire two forks simultaneously. Since forks are shared resources, the program must properly handle synchronization to avoid:

- deadlocks
- data races
- starvation
- inconsistent shared memory access

The project was implemented in C using:
- POSIX threads (`pthread`)
- mutexes
- custom timing utilities

The simulation stops when:
- a philosopher dies
- or every philosopher has eaten the required number of meals


# Project Goals

This project focuses on learning and understanding:

- multithreading
- thread synchronization
- mutex management
- shared resource protection
- concurrent programming concepts
- timing precision
- deadlock prevention
- race condition handling

# Features

- Multi-threaded philosopher simulation
- Fork protection using mutexes
- Dedicated monitor thread
- Philosopher death detection
- Deadlock prevention strategy
- Data race protection with dedicated mutexes
- Custom precise sleep implementation
- Proper mutex destruction and memory cleanup
- Optional meal count support
- Error handling for invalid arguments and thread failures

# How It Works

## Philosophers as Threads

Each philosopher is represented by an independent thread using:

```c
pthread_create()
```

This allows philosophers to:
- eat
- sleep
- think

concurrently.

## Forks as Mutexes

Each fork is represented by a mutex:

```c
pthread_mutex_t
```

Before eating, a philosopher must lock both fork mutexes.

After eating, the forks are unlocked so other philosophers may use them.

## Monitor Thread

A dedicated monitor thread continuously checks:

- whether a philosopher has died
- whether all philosophers have eaten enough times

The monitor accesses shared philosopher data safely using mutex protection.

# Synchronization

## Fork Protection

Forks are shared resources, therefore mutexes are required to ensure that only one philosopher may hold a fork at a time.


## Meal Data Protection

Each philosopher contains a dedicated:

```c
meal_mutex
```

This mutex protects:
- `last_meal_time`
- `meals_eaten`

from data races between philosopher threads and the monitor thread.


## Output Protection

A global:

```c
print_mutex
```

prevents mixed terminal output caused by multiple threads printing simultaneously.


## Simulation State Protection

A global:

```c
death_mutex
```

protects shared simulation state variables such as:
- `someone_died`
- `all_ate_enough`


# Deadlock Prevention

To avoid deadlocks, philosophers do not all pick up forks in the same order.

- Even-numbered philosophers:
  - left fork → right fork
- Odd-numbered philosophers:
  - right fork → left fork

This prevents circular waiting conditions.


# Timing

The project uses a custom:

```c
precise_sleep()
```

function instead of relying entirely on `usleep()`.

This allows more accurate timing behavior while also enabling philosophers to stop immediately if the simulation ends.


# Instructions

## Compilation

```bash
make
```

## Cleaning Object Files

```bash
make clean
```

## Full Cleanup

```bash
make fclean
```

## Recompile

```bash
make re
```


# Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```


# Parameters

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time before a philosopher dies without eating |
| `time_to_eat` | Time spent eating |
| `time_to_sleep` | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional simulation limit |


# Example Usage

## Basic Simulation

```bash
./philo 5 800 200 200
```

## Simulation With Meal Limit

```bash
./philo 5 800 200 200 10
```

# Example Output

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```


# Error Handling

The program validates:
- invalid argument count
- non-positive arguments
- thread creation failures
- mutex initialization failures
- memory allocation failures

If an error occurs, the program exits safely after cleaning allocated resources.


# Memory Management

All dynamically allocated memory is properly freed.

All mutexes are destroyed before program termination using:

```c
pthread_mutex_destroy()
```


# Testing

The project was tested using:

## Helgrind

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

Used to detect:
- data races
- synchronization issues
- thread safety problems


## DRD

```bash
valgrind --tool=drd ./philo 5 800 200 200
```

Used to verify:
- concurrent memory access correctness
- mutex usage

## Memory Leak Checks

```bash
valgrind --leak-check=full ./philo 5 800 200 200
```

Used to verify:
- memory leaks
- invalid memory operations


# Resources

## Documentation
- POSIX Threads Documentation  
  https://man7.org/linux/man-pages/man7/pthreads.7.html

- pthread_create  
  https://man7.org/linux/man-pages/man3/pthread_create.3.html

- pthread_mutex_lock  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

- gettimeofday  
  https://man7.org/linux/man-pages/man2/gettimeofday.2.html

- usleep  
  https://man7.org/linux/man-pages/man3/usleep.3.html


## Articles & References
- Dining Philosophers Problem  
  https://en.wikipedia.org/wiki/Dining_philosophers_problem

- Valgrind Documentation  
  https://valgrind.org/docs/manual/manual.html

- Concurrency Introduction  
  https://en.wikipedia.org/wiki/Concurrency_(computer_science)


# AI Usage
AI tools were used during the project for:

- understanding threading concepts
- discussing mutex behavior
- improving synchronization strategies
- understanding deadlock prevention
- reviewing timing logic
- discussing data race protection
- improving README structure and documentation

All implementation decisions, debugging, testing, architecture choices, and final code integration were completed manually.

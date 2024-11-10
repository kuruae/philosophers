# Dining Philosophers

## Overview
This project implements the classic Dining Philosophers problem, a synchronization and concurrency challenge introduced by Edsger Dijkstra in 1965. The problem illustrates synchronization issues and techniques for resolving them in concurrent programming.

## The Problem
- N philosophers sit at a round table with N forks between them
- Each philosopher needs two forks to eat
- Each philosopher follows a cycle: think → take forks → eat → sleep → repeat
- Challenge: Avoid deadlock and starvation while maximizing concurrent dining

## Implementation Details
This solution uses:
- POSIX threads for philosopher simulation
- Mutexes for fork management
- Thread synchronization to prevent deadlock
- Timestamps to track state changes
- Death monitoring to ensure philosophers don't starve

### Key Features
- Deadlock prevention using even/odd philosopher scheduling
- Real-time monitoring of philosopher states
- Clean termination when simulation goals are met
- Configurable number of philosophers and timing parameters

## Usage
```bash
# Compile the program
make

# Run with parameters:
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [times_must_eat]

# Example:
./philo 5 800 200 200 5
```

### Parameters
1. `number_of_philosophers`: Number of philosophers and forks
2. `time_to_die`: Time (ms) a philosopher can survive without eating
3. `time_to_eat`: Time (ms) it takes to eat
4. `time_to_sleep`: Time (ms) philosophers spend sleeping
5. `times_must_eat`: (Optional) Number of times each philosopher must eat

## Error Handling
- Input validation for all parameters
- Resource cleanup on program termination
- Thread safety measures
- Proper mutex management

## Technical Challenges
- Race condition prevention
- Efficient resource sharing
- Accurate timing management
- Death detection implementation

## Learning Outcomes
- Thread synchronization
- Mutex management
- Deadlock prevention
- Resource sharing in concurrent programming
- Real-time monitoring systems

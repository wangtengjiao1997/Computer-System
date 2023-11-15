# Staircase Synchronization Project

### Members:
- Tengjiao Wang
- Yongfei Lu
- Haoyu Zhang

### Project Description:
This project implements a multi-threaded simulation of customers using a staircase in a department store. The main goal is to prevent deadlock and starvation while allowing multiple customers to use the stairs efficiently. Each customer is represented by a thread, and threads are synchronized using semaphores to ensure safe access to the staircase.

### Implementation:

#### Functions:
- `sem_wait_custom(sem_t *sem, int direction)`: Waits for the semaphore ensuring that the stairs' direction is respected.
- `sem_post_custom(sem_t *sem)`: Signals the semaphore and updates the stairs' direction if necessary.
- `threadfunction(void *vargp)`: Represents a customer using the stairs, calculates the turnaround time.
- `main(int argc, char *argv[])`: Initializes semaphores, creates customer threads, and starts the simulation.

#### Testing:
The project was tested by creating multiple scenarios where customers with different directions attempted to use the stairs simultaneously. Test cases included varying the number of customers, steps, and initial direction. Each test case was designed to ensure that the program could handle concurrency without deadlocks or starvation.

#### Deadlock and Starvation Prevention:
Deadlock is prevented by ensuring that a customer thread holds the semaphore only when it can safely proceed on the stairs. Starvation is prevented by enforcing that the stairs are used in a first-come, first-served basis, without favoring any particular direction indefinitely.


#### Performance Measures:
The average turnaround time was calculated by running simulations with varying numbers of customers and steps. For 10 customer, 15 steps stair, each step take 0.1s, the average turnaround time is 0.487. The efficiency was improved by optimizing the sleep durations and minimizing the waiting time of threads.

#### Compilation and Execution:
To compile the program, run `make`. To execute the program, use `./stairs <number_of_customers> <number_of_stairs>`.

#### Contributions:
- Tengjiao Wang: Implemented the threadfunction.
- Yongfei Lu: Implemented sem_wait_custom and sem_post_custom.
- Haoyu Zhang: Implemented main function.


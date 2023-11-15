#include "stairs.h"

// You can write your own semwait function that can call sem_wait(sem) or sem_trywait(sem)
// in addition to checking/setting proper variables
// properly use pthread_mutex_lock/unlock
 

// You can write your own sempost function that call sem_post(sem)
// in addition to checking/setting proper variables
// properly use pthread_mutex_lock/unlock
// Global variables definition
int current_direction = 0;
int customers_on_stairs = 0;
pthread_mutex_t direction_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t stair_sem;
pthread_t tid[MAX_CUSTOMERS];



void sem_wait_custom(sem_t *sem, int direction) {
    pthread_mutex_lock(&direction_mutex);
    // Wait until the stairs are free or the current direction is the same as the customer's direction.
    while (customers_on_stairs > 0 && current_direction != direction) {
        pthread_mutex_unlock(&direction_mutex);
        usleep(1000); // Sleep for a short time to prevent busy waiting
        pthread_mutex_lock(&direction_mutex);
    }
    // Set the current direction to the customer's direction and increment the number of customers on the stairs.
    current_direction = direction;
    customers_on_stairs++;
    pthread_mutex_unlock(&direction_mutex);
    sem_wait(sem);
}

void sem_post_custom(sem_t *sem) {
    pthread_mutex_lock(&direction_mutex);
    // Decrement the number of customers on the stairs.
    customers_on_stairs--;
    // If there are no more customers on the stairs, reset the current direction.
    if (customers_on_stairs == 0) {
        current_direction = 0;
    }
    pthread_mutex_unlock(&direction_mutex);
    sem_post(sem);
}

void *threadfunction(void *vargp) {
    thread_arg_t *arg = (thread_arg_t *)vargp;
    
    // Attempt to access the stairs
    sem_wait_custom(&stair_sem, arg->direction);


    gettimeofday(&arg->start_time, NULL); 
    printf("Customer %d is using the stairs in direction %d\n", arg->index, arg->direction);

    int steps = *((int*)vargp); 
    usleep(steps * 100000); // 0.5 seconds per step

    gettimeofday(&arg->end_time, NULL); 
    sem_post_custom(&stair_sem);

    // Calculate turnaround time
    long seconds = arg->end_time.tv_sec - arg->start_time.tv_sec;
    long microseconds = arg->end_time.tv_usec - arg->start_time.tv_usec;
    double turnaround_time = seconds + microseconds*1e-6;
    
    printf("Customer %d turnaround time: %.3f seconds\n", arg->index, turnaround_time);

    free(arg); // Free the memory allocated for the thread argument
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_customers> <number_of_stairs>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int customerNum = atoi(argv[1]);
    int stairNum = atoi(argv[2]);
    // Initialize semaphore and mutex
    sem_init(&stair_sem, 0, stairNum);
    pthread_mutex_init(&direction_mutex, NULL);

    // Create threads
    for (int i = 0; i < customerNum; i++) {
        thread_arg_t *arg = malloc(sizeof(thread_arg_t));
        arg->index = i;
        arg->direction = (rand() % 2) * 2 - 1; // Randomly choose 1 or -1
        gettimeofday(&arg->start_time, NULL);

        pthread_create(&tid[i], NULL, threadfunction, arg);
    }

    // Join threads
    for (int i = 0; i < customerNum; i++) {
        pthread_join(tid[i], NULL);
    }

    // Cleanup
    sem_destroy(&stair_sem);
    pthread_mutex_destroy(&direction_mutex);

    return 0;
}

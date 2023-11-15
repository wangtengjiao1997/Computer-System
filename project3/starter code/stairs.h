#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_CUSTOMERS 30
#define MAX_ON_STAIRS 5
#define UP 1
#define DOWN -1

typedef struct thread_arg {
    int index;
    int direction; // 1 for up, -1 for down
    struct timeval start_time;
    struct timeval end_time;
} thread_arg_t;


#define MAX_CUSTOMERS 30
#define MAX_STAIRS 13
#define MAX_CUSTOMERS_ON_STAIRS 2 // Adjust as needed

// Global variables
extern int current_direction;
extern int customers_on_stairs;
extern pthread_mutex_t direction_mutex;
extern sem_t stair_sem;

// Timing variables - These can be used for calculating turnaround time
extern struct timeval start_time[MAX_CUSTOMERS];

// Thread array
extern pthread_t tid[MAX_CUSTOMERS];

// Helper function declarations
void sem_wait_custom(sem_t *sem, int direction);
void sem_post_custom(sem_t *sem);



#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg) {
    if (pthread_mutex_trylock(&lock) == 0) { // Non-blocking call
        // Critical section
        printf("Thread %d has entered the critical section.\n", *(int *)arg);
        // Simulate work
        sleep(2);
        printf("Thread %d is leaving the critical section.\n", *(int *)arg);
        pthread_mutex_unlock(&lock);
    } else {
        // Lock not acquired
        printf("Thread %d could not acquire the lock.\n", *(int *)arg);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_create(&t1, NULL, thread_func, &id1);
    pthread_create(&t2, NULL, thread_func, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}


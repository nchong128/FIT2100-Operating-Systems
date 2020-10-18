#include <stdio.h>      /* standard I/O routines */
#include <pthread.h>    /* pthread functions and data structures */
#include <unistd.h>     /* we will use sleep() later on in prac */
#include <stdlib.h>     /* needed for exit() function */


void* sayHello(void* data) {
    int i = (int) data;
    pthread_t tid = pthread_self();

    pthread_detach(pthread_self());
    printf("Hello from thread %lu. I was created in iteration %d\n", tid, i);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    int numThreads = atoi(argv[1]);
    pthread_t main_id = pthread_self();
    pthread_t tid[numThreads];
    int rc;
    int i;

    for (i= 0; i < numThreads; i++) {
        if (i % 4 == 0) {
            sleep(1);
        }

        rc = pthread_create(&tid[i], NULL, sayHello, (void*) i);
        printf("I am thread %lu. Created new thread %lu in iteration %d\n", main_id, tid[i] , i);
    }

    pthread_exit(NULL);
}
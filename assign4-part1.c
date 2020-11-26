
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 

//prototypes
void createPhilosophers(int nthreads);
void *philosophers(void *pVoid);

int main(int argc, char** argv) {
    //check num of args
    if (argc != 2){
        printf("ERROR: Incorrect number of arguments");
        exit(101);
    }
    printf("Assignment 4: # of threads = %s\n",argv[1]);
    
    char *p;
    int nthreads = strtol(argv[1], &p, 10);
    createPhilosophers(nthreads);
    return (EXIT_SUCCESS);
}

void createPhilosophers(int nthreads){
    pthread_t tid[nthreads];
    long i,j;
    int error;
    //create and call threads func
    for(i = 1; i <= nthreads; i++){
        if(error = pthread_create(&tid[i],NULL,philosophers,(void *) i)){
            printf("Failed to create thread: %d\n",error);
            break;
        }
    }
    //join and exit threads
    for(j = 1; j <= nthreads; j++){
        if(error = pthread_join(tid[j],NULL)){
            printf("Failed to join thread: %d\n",error);
            break;
        }
    }
    printf("%d threads have been completed/joined successfully!\n",nthreads);
}

//threads func
void *philosophers(void *pVoid){

    long num = (long) pVoid;

    printf("This is philosopher %ld\n",num);

    return NULL;

}
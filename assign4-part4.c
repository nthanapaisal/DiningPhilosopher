#define _XOPEN_SOURCE 500 // for usleep
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#include <string.h>
#include <pthread.h> 

//prototypes
void createPhilosophers();
void *philosophers(void *pVoid);
void thinking(int threadIndex);
void pickUpChopSticks(int threadIndex);
void eating(int threadIndex);
void putDownChopsitcks(int threadIndex);

//Globals
pthread_mutex_t *chopsticks;
int nthreads;

int main(int argc, char** argv) {
    //check num of args
    if (argc != 2){
        printf("ERROR: Incorrect number of arguments");
        exit(101);
    }
    printf("Assignment 4: # of threads = %s\n",argv[1]);
    
    char *p;
    nthreads = strtol(argv[1], &p, 10);

    createPhilosophers();
    return (EXIT_SUCCESS);
}

void createPhilosophers(){
    pthread_t tid[nthreads];
    chopsticks = malloc(nthreads * sizeof(chopsticks[0]));
    long i,j;
    int error;

    //initalized chopsticks
    for(i = 0; i < nthreads; i++){
        chopsticks[i] = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    }

    //Create threads
    for(i = 0; i < nthreads; i++){
        if(error = pthread_create(&tid[i],NULL,philosophers,(void *) i)){
            printf("Failed to create thread: %d\n",error);
            break;
        }
        
    }
    
    //join threads
    for(j = 0; j < nthreads; j++){
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
    thinking(num);
    pickUpChopSticks(num);
    eating(num);
    putDownChopsitcks(num);
    return NULL;

}

void thinking(int threadIndex){
    printf("Philosopher #%d start thinking\n",threadIndex);
    //get random number / by 501 to get range 1-500
    int time = rand() % 501;
    usleep(time);
    printf("Philosopher #%d end thinking\n",threadIndex);
}

void pickUpChopSticks(int threadIndex){
    int error;
    while(1){
    
        //cant pick up wait try left == 0 means sucess
        if(!pthread_mutex_trylock(&chopsticks[(threadIndex+1)%nthreads])){
            //try right
            if(!pthread_mutex_trylock(&chopsticks[threadIndex])){
                //pick up print pick up left
                printf("Philo #%d pick up left chopstick: (index %d)\n",threadIndex,(threadIndex+1)%nthreads);
                //pick up print pick up right
                printf("Philo #%d pick up  right chopstick: (index %d)\n",threadIndex,threadIndex);
                return;
            }else{
                //unlock if cant get right
                pthread_mutex_unlock(&chopsticks[(threadIndex+1)%nthreads]);
            }
        }
    }   

}

void eating(int threadIndex){
    printf("Philosopher #%d start eating\n",threadIndex);
    //get random number / by 501 to get range 1-500
    int time = rand() % 501;
    //sleep
    usleep(time);
    printf("Philosopher #%d end eating\n",threadIndex);
}

void putDownChopsitcks(int threadIndex){
    //unlock both chopsticks
    pthread_mutex_unlock(&chopsticks[(threadIndex+1)%nthreads]);
    printf("Philo #%d put down left chopstick: (index %d)\n",threadIndex,(threadIndex+1)%nthreads);
    pthread_mutex_unlock(&chopsticks[threadIndex]);
    printf("Philo #%d put down right chopstick: (index %d)\n",threadIndex,threadIndex);

}
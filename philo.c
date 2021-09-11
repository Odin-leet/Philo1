#include "philo.h"
int numofphilo;

void    *routine(void *arg)
{   
    int index;
    index = *(int*)arg;
    printf("loooooooool \n");
    pthread_mutex_lock(&forks[index]);
    printf("philosopher %d is eating \n", index + 1);
    pthread_mutex_lock(&forks[(index + 1) % numofphilo]);
    usleep(100);
    pthread_mutex_unlock(&forks[index]);
    pthread_mutex_unlock(&forks[index + 1]);
    
    //printf("thread created |%d| \n",index);
    
    return(NULL);
}

int     main(int argc, char **argv)
{
    int i;
    int c;
    int j;

    forks = malloc (sizeof(pthread_mutex_t) * i);
    pthread_t thread[atoi(argv[1])];
    pthread_mutex_init(&forks,NULL);
    numofphilo = atoi(argv[1]);
    i =  atoi(argv[1]);
    j = 0;
    while (j < i)
    {
        pthread_create(&thread[j], NULL, &routine, &j);
        usleep(100);
        j++;
    }
    printf("number of philo %d \n", atoi(argv[1]));
    c = 0;
    while (c < i)
    {
        pthread_join(thread[c],NULL);
        c++;
    }
    return(0);
}

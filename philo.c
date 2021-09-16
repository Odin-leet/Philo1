#include "philo.h"

void    *routine(void *arg)
{   
    
    t_philo *pl;
    pl = (t_philo*)arg;
    printf("loooooooool \n");
    pthread_mutex_lock(&pl->forks[pl->index]);
    printf("philosopher %d is eating \n", pl->index + 1);
    pthread_mutex_lock(&pl->forks[(pl->index + 1) % pl->numofphilo]);
    usleep(100);
    pthread_mutex_unlock(&pl->forks[pl->index]);
    pthread_mutex_unlock(&pl->forks[pl->index + 1]);
    
    //printf("thread created |%d| \n",index);
    
    return(NULL);
}

int     main(int argc, char **argv)
{
    int i;
    int c;
    int j;

    t_philo gl;
    gl.forks = malloc (sizeof(pthread_mutex_t) * i);
    pthread_t thread[atoi(argv[1])];
    pthread_mutex_init(gl.forks,NULL);
    gl.numofphilo = atoi(argv[1]);
    i =  atoi(argv[1]);
    j = 0;
    while (j < i)
    {
        gl.index = j;
        pthread_create(&thread[j], NULL, &routine, &gl);
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

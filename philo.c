#include "philo.h"
void    *routine(void *arg)
{   
    int index;
    index = *(int*)arg;
    printf("thread created |%d| \n",index);
    return(NULL);
}

int     main(int argc, char **argv)
{
    int i;
    int c;
    int j;
    pthread_mutex_t *fork;

    fork = malloc (sizeof(pthread_mutex_t) * i);
    pthread_t thread[atoi(argv[1])];

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

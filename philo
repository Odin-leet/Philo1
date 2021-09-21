#include "philo.h"
long int  time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) / 1e-6 +  (end->tv_usec - start->tv_usec);
}

// next step current timee fettomeofday() 
void    *routine(void *arg)
{   
          struct timeval start;
          struct timeval end;

    t_philo *pl;
    pl = (t_philo*)arg;
    int index = pl->index;
    while (1)
    {
    gettimeofday(&start, NULL);
    

     //printf("philosopher %d is thinking \n", index + 1);   
    pthread_mutex_lock(&pl->forks[index]);
    pthread_mutex_lock(&pl->forks[(index + 1)  % pl->numofphilo]);
     gettimeofday(&end, NULL);

    if (time_diff(&start,&end) > pl->timetodie)
   
    {
        printf("philosopher %d die ", index + 1);
        break;
    }
    printf("time 1 %ld ", time_diff(&start,&end) * 1000);
    printf("philosopher %d is eating \n",index + 1);
    usleep(pl->timetoeat * 1000);
    
    pthread_mutex_unlock(&pl->forks[index]);
    pthread_mutex_unlock(&pl->forks[(index + 1) % pl->numofphilo]);
   printf("philosopher %d is sleeping \n", index + 1);
    usleep(pl->timetosleep * 1000);
    
    }
   // while (1)
   // {
   //     printf("philosopher %d is thinking \n", pl->index + 1);
   // 
   // }
    //printf("thread created |%d| \n",index);
    
    return(NULL);
}

int     main(int argc, char **argv)
{
    int i;
    int c;
    int j;

    time_t t;
  //
  //printf("seconds : %ld\nmicro seconds %ld",
  //current_time.tv_sec, current_time.tv_usec);
  //t = current_time.tv_sec;
  //  printf("seconds : %ld\nmicro seconds",current_time.tv_sec);

    t_philo gl;
    gl.forks = malloc (sizeof(pthread_mutex_t) * i);
    pthread_t thread[atoi(argv[1])];
    gl.timetodie = atoi(argv[2]);
    gl.timetoeat = atoi(argv[3]);
    gl.timetosleep = atoi(argv[4]);
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
        // pthread_join(thread[c],NULL);
        // c++;
    }
    return(0);
}

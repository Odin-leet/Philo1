#include "philo.h"

long int  time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) / 1e-6) +  (end->tv_usec - start->tv_usec);
}

void    *routine(void *arg)
{
 
    t_philo *pl;
    int     index;
    int     time_diff1;

    pl = (t_philo*)arg;
    index = pl->index;
    time_diff1 = time_diff(&pl->dl[index].start,&pl->dl[index].end);
    while (1)
    {
        gettimeofday(&pl->dl[index].start, NULL); 
        pthread_mutex_lock(&pl->forks[index]);
        pthread_mutex_lock(&pl->print);
        printf("philosopher %d took the right fork\n",index  + 1);
        pthread_mutex_unlock(&pl->print);
        pthread_mutex_lock(&pl->forks[(index + 1) % pl->numofphilo] );
        gettimeofday(&pl->dl[index].end,NULL);
        if((time_diff1 = time_diff(&pl->dl[index].start,&pl->dl[index].end)) > pl->timetodie * 1000)
        {
            pthread_mutex_lock(&pl->print);
            printf("philosopher %d die\n",index + 1);
            printf("time diff = %d  time to die = %d\n",time_diff1, pl->timetodie);
            pl->reminder = 1;
            break;
        }
        pthread_mutex_lock(&pl->print);
        printf("philosopher %d took the left fork\n",index + 1);
        pthread_mutex_unlock(&pl->print);
        pthread_mutex_lock(&pl->print);
        printf("philosopher %d is eating \n",index +1);
        pthread_mutex_unlock(&pl->print);
        usleep(pl->timetoeat * 1000);
        pthread_mutex_unlock(&pl->forks[index]);
        pthread_mutex_unlock(&pl->forks[(index + 1) % pl->numofphilo]);
        pthread_mutex_lock(&pl->print);
        printf("philosopher %d is sleeping\n",index + 1);
        pthread_mutex_unlock(&pl->print);
        usleep(pl->timetosleep * 1000);
    }
    return (NULL);
}

void    gettinginfos(char **argv, t_philo *gl)
{
    gl->numofphilo = atoi(argv[1]);
    gl->timetodie = atoi(argv[2]);
    gl->timetoeat = atoi(argv[3]);
    gl->timetosleep = atoi(argv[4]);
    gl->reminder = 0;
}

int main(int argc, char **argv)
{
    t_philo gl;
    int     j;
    pthread_t   thread[atoi(argv[1])];

    gettinginfos(argv, &gl);
    gl.dl = malloc(sizeof(t_data*) * gl.numofphilo);   
    gl.forks = malloc(sizeof(pthread_mutex_t) * gl.numofphilo);
    j = 0;
    pthread_mutex_init(&gl.print, NULL);
    while (j < gl.numofphilo)
    {
         pthread_mutex_init(&gl.forks[j],NULL);
         j++;
    }
    j = 0;
    while(j < gl.numofphilo)
    {
        gl.index = j;
        gl.dl[j].pid = j;
        pthread_create(&thread[j], NULL, &routine, &gl);
        usleep(100);
        if (gl.reminder == 1)
        {
            return (0);
        }
        j++;
    }
    j = 0;
    while (j <  gl.numofphilo)
    {
        pthread_join(thread[j], NULL);
        j++;
    }
    return (0); 
}
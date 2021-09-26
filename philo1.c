#include "philo.h"

long int      timepassed(long int start)
{   
    struct timeval right;
    gettimeofday(&right, NULL);
    return((right.tv_sec * 1000) + (right.tv_usec / 1000) - start);
}


long int  time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) / 1e-6) +  (end->tv_usec - start->tv_usec);
}


int    checktab(int *tab, int j, int c)
{
    int i;

    i = 0;
    while (i < j)
    {
        if (tab[i] >= c)
        {
            i++;
        }
        
        else
        return 0;
    }
    return(1);
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
        printf("%ld philosopher %d took the right fork\n",timepassed(pl->start),index  + 1);
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
        printf("%ld philosopher %d took the left fork\n",timepassed(pl->start),index + 1);
        printf("%ld philosopher %d is eating \n",timepassed(pl->start),index +1);
       pthread_mutex_unlock(&pl->print);
        usleep(pl->timetoeat * 1000);
         pthread_mutex_unlock(&pl->forks[index]);
        pthread_mutex_unlock(&pl->forks[(index + 1) % pl->numofphilo]);
        
     \
        
        if(pl->timesme == 1)
        pl->tab[index]++;
        if (pl->timesme == 1)
        if(checktab(pl->tab, pl->numofphilo, pl->timesme2) == 1)
        {
            pthread_mutex_lock(&pl->print);
            printf("all the philos eat the times must eat %d\n ",pl->timesme2);
            break;
        }
        
       
        pthread_mutex_lock(&pl->print);
        printf("%ld philosopher %d is sleeping\n",timepassed(pl->start),index + 1);
        pthread_mutex_unlock(&pl->print);
        usleep(pl->timetosleep * 1000);
    } 
    return (NULL);
}

void    gettinginfos(char **argv, t_philo *gl)
{
    struct timeval now;

    gettimeofday(&now,NULL);
    gl->numofphilo = atoi(argv[1]);
    gl->timetodie = atoi(argv[2]);
    gl->timetoeat = atoi(argv[3]);
    gl->timetosleep = atoi(argv[4]);
    gl->reminder = 0;
    gl->timesme = 0;
    gl->start = ((now.tv_sec * 1000)  + (now.tv_usec / 1000));
    
}

int main(int argc, char **argv)
{
    t_philo gl;
    int     j;
    pthread_t   thread[atoi(argv[1])];
    gettinginfos(argv, &gl);
    printf("argc = %d\n",argc);
    if (argc == 6)
    {
        gl.timesme = 1;
        gl.timesme2 = atoi(argv[5]);
        gl.tab = malloc(sizeof(int) * gl.numofphilo);
        j = -1;
        while (++j < gl.numofphilo)
        gl.tab[j] = 0;
    }
    gl.dl = malloc(sizeof(t_data*) * gl.numofphilo);   
    gl.forks = malloc(sizeof(pthread_mutex_t) * gl.numofphilo);
    j = 0;
    pthread_mutex_init(&gl.print, NULL);
    while (j < gl.numofphilo)
    {
         pthread_mutex_init(&gl.forks[j],NULL);
         j++;
         if (gl.reminder == 1)
        return(0);
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
        if (gl.reminder == 1)
        return(0);
    }
    return (0); 
}

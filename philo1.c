#include "philo.h"
long int      timepassed(long int start)
{   
	struct timeval right;
	gettimeofday(&right, NULL);
	return((right.tv_sec * 1000) + (right.tv_usec / 1000) - start);
}

long int    time_now()
{
	struct timeval right1;
	gettimeofday(&right1, NULL);
	return((right1.tv_sec * 1000) + (right1.tv_usec / 1000));
}
//long int  time_off(struct timeval *start)
//{
//	return ((start->tv_sec) / 1e-6) +  (start->tv_usec);
//}
//
//long int  time_diff(struct timeval *start, struct timeval *end)
//{
//	return ((end->tv_sec - start->tv_sec) * 1e-6) +  (end->tv_usec - start->tv_usec);
//}

void    eating(t_philo *rl, int index)
{
	pthread_mutex_lock(&rl->forks[index]);
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d took the right fork\n",timepassed(rl->start),index  + 1);
	pthread_mutex_unlock(&rl->print);
	pthread_mutex_lock(&rl->forks[(index + 1) % rl->numofphilo] );
	pthread_mutex_lock(&rl->print);

	printf("%ld philosopher %d took the left fork\n",timepassed(rl->start),index + 1);
    rl->dl[index].end = time_now();
    printf("end ==== %ld |||||||\n\n ",rl->dl[index].end);
	pthread_mutex_unlock(&rl->print);
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d is eating \n",timepassed(rl->start),index +1);
	pthread_mutex_unlock(&rl->print);

	usleep(rl->timetoeat * 1000);
	pthread_mutex_unlock(&rl->forks[index]);
	pthread_mutex_unlock(&rl->forks[(index + 1) % rl->numofphilo]);
}
void    sleeping(t_philo *rl, int index)
{
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d is sleeping\n",timepassed(rl->start),index + 1);
	pthread_mutex_unlock(&rl->print);
	usleep(rl->timetosleep * 1000);
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
	//time_diff1 = time_diff(&pl->dl[index].start,&pl->dl[index].end);
	while (1)
	{ 


		eating(pl , index);

		if(pl->timesme == 1)
			pl->tab[index]++;
		sleeping(pl, index);  
	} 
	return (NULL);
}

void    gettinginfos(char **argv, t_philo *gl)
{
	struct timeval now;
    int i = 0;
	gettimeofday(&now,NULL);
	gl->numofphilo = atoi(argv[1]);
	gl->timetodie = atoi(argv[2]);
	gl->timetoeat = atoi(argv[3]);
	gl->timetosleep = atoi(argv[4]);
	gl->reminder = 0;
	gl->timesme = 0;
    // int i = 0;
    // while (i < gl->numofphilo)
    // {

    // }
	gl->start = ((now.tv_sec * 1000)  + (now.tv_usec / 1000));

}

int main(int argc, char **argv)
{
	t_philo gl;
	int     j;
	int time_diff1;
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
	gl.dl = malloc(sizeof(t_data) * gl.numofphilo);   
    int i;
    i = 0;
   //
   
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
    i = 0;
    while(i < gl.numofphilo)
    {
        gl.dl[i].end = time_now();
        i++;

    }
	while(j < gl.numofphilo)
	{
		gl.index = j;
		gl.dl[j].pid = j;
        gl.timetoeat = time_now();
		pthread_create(&thread[j], NULL, &routine, &gl);
		usleep(100);
		j++;
	}
	int k;
	


	k = 1;
	while (k == 1)
	{
		i = 0;
        
		while (i <  gl.numofphilo)
		{

			if (gl.timesme == 1)
				if(checktab(gl.tab, gl.numofphilo, gl.timesme2) == 1)
				{
					pthread_mutex_lock(&gl.print);
					printf("all the philos eat the times must eat %d\n ",gl.timesme2);
					k = 0;
					break;
				}

			if(timepassed(gl.dl[i].end) > gl.timetodie )
			{
				printf("%ld |||||| \n",timepassed(gl.dl[i].end));
				pthread_mutex_lock(&gl.print);
				printf("%ld philosopher %d die\n",timepassed(gl.start),i + 1);
				printf("time diff = %d  time to die = %d\n",time_diff1/ 1000, gl.timetodie);
				gl.reminder = 1;
				k = 0;
				break;
			}
			i++;
		}
	}
	return (0); 
}

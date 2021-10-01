#include "philo.h"

void	checktte(t_philo *gl, char **argv)
{
	int	j;

	gl->timesme = 1;
	gl->timesme2 = ft_atoi(argv[5]);
	gl->tab = malloc(sizeof(int) * gl->numofphilo);
	j = -1;
	while (++j < gl->numofphilo)
		gl->tab[j] = 0;
}

void	gettinginfos(char **argv, t_philo *gl)
{
	struct timeval	now;
	int				i;

	i = 0;
	gettimeofday(&now, NULL);
	gl->numofphilo = ft_atoi(argv[1]);
	gl->timetodie = ft_atoi(argv[2]);
	gl->timetoeat = ft_atoi(argv[3]);
	gl->timetosleep = ft_atoi(argv[4]);
	gl->reminder = 0;
	gl->index = 0;
	gl->timesme = 0;
	gl->start = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	eating(t_philo *rl, int index)
{
	pthread_mutex_lock(&rl->forks[index]);
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d took the right fork\n",
		timepassed(rl->start), index + 1);
	pthread_mutex_unlock(&rl->print);
	pthread_mutex_lock(&rl->forks[(index + 1) % rl->numofphilo]);
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d took the left fork\n",
		timepassed(rl->start), index + 1);
	pthread_mutex_unlock(&rl->print);
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d is eating --  \n",
		timepassed(rl->start), index + 1);
	pthread_mutex_unlock(&rl->print);
	rl->dl[index].end = time_now();
	mysleep(rl->timetoeat);
	pthread_mutex_unlock(&rl->forks[index]);
	pthread_mutex_unlock(&rl->forks[(index + 1) % rl->numofphilo]);
}

void	*routine(void *arg)
{
	int		index;
	int		time_diff1;
	t_philo	*pl;

	pl = (t_philo *)arg;
	index = pl->index;
	while (1)
	{
		eating(pl, index);
		if (pl->timesme == 1)
			pl->tab[index]++;
		sleeping(pl, index);
	}
	return (NULL);
}

void	traitingtreads(t_philo *gl, char **argv)
{
	int			j;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * gl->numofphilo);
	gl->forks = malloc(sizeof(pthread_mutex_t) * gl->numofphilo);
	j = -1;
	while (++j < gl->numofphilo)
		pthread_mutex_init(&gl->forks[j], NULL);
	j = -1;
	while (++j < gl->numofphilo)
		gl->dl[j].end = time_now();
	j = -1;
	while (++j < gl->numofphilo)
	{
		gl->index = j;
		pthread_create(&thread[j], NULL, &routine, gl);
		usleep(100);
	}
}

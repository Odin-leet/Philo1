#include "philo.h"

long	int	time_now(void)
{
	struct timeval	right1;

	gettimeofday(&right1, NULL);
	return ((right1.tv_sec * 1000) + (right1.tv_usec / 1000));
}

void	mysleep(int time)
{
	long int	now;

	now = time_now();
	usleep(time * 1000 * 0.85);
	while (time_now() < now + time)
		continue ;
}

long	int	timepassed(long int start)
{
	struct timeval	right;

	gettimeofday(&right, NULL);
	return ((right.tv_sec * 1000) + (right.tv_usec / 1000) - start);
}

void	sleeping(t_philo *rl, int index)
{
	pthread_mutex_lock(&rl->print);
	printf("%ld philosopher %d is sleeping\n", timepassed(rl->start), index + 1);
	pthread_mutex_unlock(&rl->print);
	mysleep(rl->timetosleep);
}

int	checktab(int *tab, int j, int c)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (tab[i] >= c)
			i++;
		else
			return (0);
	}
	return (1);
}

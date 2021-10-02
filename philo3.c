/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:40:32 by aali-mou          #+#    #+#             */
/*   Updated: 2021/10/02 17:54:59 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *pl, int index, char *s)
{
	if (pl->p == 1)
	{
		pthread_mutex_lock(&pl->print);
		printf("%ld philosopher %d %s\n",
			timepassed(pl->start), index + 1, s);
		pthread_mutex_unlock(&pl->print);
	}
}

int	gettinginfos(char **argv, int argc, t_philo *gl)
{
	if (argc != 6 && argc != 5)
		return (0);
	if (!ft_atoi(argv[1], &gl->numofphilo))
		return (0);
	if (!ft_atoi(argv[2], &gl->timetodie))
		return (0);
	if (!ft_atoi(argv[3], &gl->timetoeat))
		return (0);
	if (!ft_atoi(argv[4], &gl->timetosleep))
		return (0);
	if (argc == 6)
	{
		gl->timesme = 1;
		if (!ft_atoi(argv[5], &gl->timesme2))
			return (0);
	}
	intialisation(gl);
	gl->start = time_now();
	gl->check1 = (int *)malloc(sizeof(int) * gl->numofphilo);
	gl->end = (long int *)malloc(sizeof(long int) * gl->numofphilo);
	return (1);
}

void	eating(t_philo *pl, int index)
{
	pthread_mutex_lock(&pl->forks[index]);
	if (pl->p)
		printing(pl, index, "took the right fork");
	pthread_mutex_lock(&pl->forks[(index + 1) % pl->numofphilo]);
	if (pl->p)
		printing(pl, index, "took the left for");
	if (pl->p)
		printing(pl, index, "is eating ");
	pl->end[index] = time_now();
	pl->iseating[index] = 1;
	mysleep(pl->timetoeat);
	pl->iseating[index] = 0;
	pthread_mutex_unlock(&pl->forks[index]);
	pthread_mutex_unlock(&pl->forks[(index + 1) % pl->numofphilo]);
	pl->check1[index]++;
	if (pl->check1[index] >= pl->timesme2)
		pl->check2++;
}

void	*routine(void *arg)
{
	int		index;
	t_philo	*pl;

	pl = (t_philo *)arg;
	index = pl->index;
	while (1)
	{
		eating(pl, index);
		printing(pl, index, "is sleeping");
		pthread_mutex_lock(&pl->print);
		mysleep(pl->timetosleep);
		printing(pl, index, "is thinking");
		if (pl->p == 0)
		{
			pthread_mutex_unlock(&pl->print);
			return (NULL);
		}
		pthread_mutex_unlock(&pl->print);
	}
	return (NULL);
}

int	traitingtreads(t_philo *gl)
{
	int			j;

	if (gl->numofphilo == 0)
		return (0);
	gl->threads = malloc(sizeof(pthread_t) * gl->numofphilo);
	gl->forks = malloc(sizeof(pthread_mutex_t) * gl->numofphilo);
	j = -1;
	while (++j < gl->numofphilo)
		pthread_mutex_init(&gl->forks[j], NULL);
	j = -1;
	while (++j < gl->numofphilo)
	{
		gl->end[j] = time_now();
		gl->check1[j] = 0;
	}
	j = -1;
	while (++j < gl->numofphilo)
	{
		gl->index = j;
		pthread_create(gl->threads + j, NULL, &routine, gl);
		usleep(100);
	}
	return (1);
}

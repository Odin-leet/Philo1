/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:40:56 by aali-mou          #+#    #+#             */
/*   Updated: 2021/10/02 17:43:08 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	int	time_now(void)
{
	struct timeval	right1;

	gettimeofday(&right1, NULL);
	return ((right1.tv_sec * 1000) + (long int)(right1.tv_usec / 1000));
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
	return ((right.tv_sec * 1000) + (long int)(right.tv_usec / 1000) - start);
}

void	sleeping(t_philo *pl, int index)
{		
	pthread_mutex_lock(&pl->print);
	if (pl->p)
		printf("%ld philosopher %d is sleeping\n",
			timepassed(pl->start), index + 1);
	pthread_mutex_unlock(&pl->print);
	mysleep(pl->timetosleep);
	pthread_mutex_lock(&pl->print);
	if (pl->p)
		printf("%ld philosopher %d is thinking\n",
			timepassed(pl->start), index + 1);
	pthread_mutex_unlock(&pl->print);
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

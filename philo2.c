/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:40:27 by aali-mou          #+#    #+#             */
/*   Updated: 2021/10/02 11:20:31 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	intialisation(t_philo *gl)
{
	int	i;

	i = 0;
	gl->reminder = 0;
	gl->index = 0;
	gl->check2 = 0;
	gl->p = 1;
	gl->iseating = malloc(sizeof(int) * gl->numofphilo);
	while(i < gl->numofphilo)
	{
		gl->iseating[i] = 0;
		i++;
	}
}

int	mainhelper(t_philo *gl, int i, int k, int check)
{
	check = 0;
	while (i < gl->numofphilo)
	{
		if (gl->timesme == 1)
			if (gl->check2 >= gl->numofphilo)
			{
				pthread_mutex_lock(&gl->print);
				gl->p = 0;
				pthread_mutex_unlock(&gl->print);	
				k = 0;
				break;
			}
		if (gl->iseating[i] == 0)
		if (timepassed(gl->end[i]) > gl->timetodie)
		{
			pthread_mutex_lock(&gl->print);
			gl->p = 0;
			printf("%ld philosopher %d die\n", timepassed(gl->start), i + 1);
			pthread_mutex_unlock(&gl->print);
			k = 0;
			break ;
		}
		i++;
	}
	return (k);
}

int	main(int argc, char **argv)
{
	t_philo		gl;
	int			i;
	int			k;
	int			check;

	check = 0;
	if (gettinginfos(argv, argc, &gl) == 0)
	{
		printf("param problem\n");
		return (0);
	}
	if (gl.numofphilo == 0)
		return (0);
	k = 1;
	while (k == 1)
	{
		i = 0;
		k = mainhelper(&gl, i, k, check);
	}
	k = 0;
	while (k < gl.numofphilo)
	{
		pthread_join(gl.threads[k], NULL);
		k++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aali-mou <aali-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:40:46 by aali-mou          #+#    #+#             */
/*   Updated: 2021/10/02 10:52:18 by aali-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>



typedef struct philo{
	int				numofphilo;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				timesme;
	int				timesme2;
	int				p;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				*iseating;
	int				index;
	int				reminder;
	long int		start;
	int				check2;
	long int	*end;
	int			*check1;
	
}				t_philo;

int			ft_atoi(char *str, int *number);
int			gettinginfos(char **argv, int argc, t_philo *gl);
void		eating(t_philo *rl, int index);
void		*routine(void *arg);
int			traitingtreads(t_philo *gl);
long int	timepassed(long int start);
void		mysleep(int time);
long int	time_now(void);
void		sleeping(t_philo *rl, int index);
int			checktab(int *tab, int j, int c);
void		intialisation(t_philo *gl);

#endif

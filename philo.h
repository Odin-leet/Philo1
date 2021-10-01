#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct data{
	long int	end;
}				t_data;

typedef struct philo{
	int				numofphilo;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				timesme;
	int				timesme2;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				index;
	int				reminder;
	long int		start;
	int				*tab;
	t_data			*dl;
}				t_philo;
int			ft_atoi(const char *str);
void		checktte(t_philo *gl, char **argv);
void		gettinginfos(char **argv, t_philo *gl);
void		eating(t_philo *rl, int index);
void		*routine(void *arg);
void		traitingtreads(t_philo *gl, char **argv);
long int	timepassed(long int start);
void		mysleep(int time);
long int	time_now(void);
void		sleeping(t_philo *rl, int index);
int			checktab(int *tab, int j, int c);

#endif

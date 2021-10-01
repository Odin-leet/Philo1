#include "philo.h"

int		mainhelper(t_philo *gl, int i, int k, int check)
{
	while (i < gl->numofphilo)
		{
			if (gl->timesme == 1)
			{
				check = checktab(gl->tab, gl->numofphilo, gl->timesme2);
				if (check == 1)
				{
					pthread_mutex_lock(&gl->print);
					k = 0;
					break ;
				}
			}
			if (timepassed(gl->dl[i].end) > gl->timetodie)
			{
				pthread_mutex_lock(&gl->print);
				printf("%ld philosopher %d die\n", timepassed(gl->start), i + 1);
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

	if (gettinginfos(argv, argc, &gl) == 0)
	{
		printf("param problem\n");
		return(0);
	}
	if (gl.numofphilo == 0)
	return (0);
	k = 1;
	while (k == 1)
	{
		i = 0;
		k = mainhelper(&gl, i, k, check);
	}
	return (0);
}

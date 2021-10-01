#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		gl;
	int			i;
	int			k;
	int			check;

	gettinginfos(argv, &gl);
	if (argc == 6)
		checktte(&gl, argv);
	gl.dl = malloc(sizeof(t_data) * gl.numofphilo);
	traitingtreads(&gl, argv);
	k = 1;
	while (k == 1)
	{
		i = 0;
		while (i < gl.numofphilo)
		{
			if (gl.timesme == 1)
			{
				check = checktab(gl.tab, gl.numofphilo, gl.timesme2);
				if (check == 1)
				{
					pthread_mutex_lock(&gl.print);
					k = 0;
					break ;
				}
			}
			if (timepassed(gl.dl[i].end) > gl.timetodie)
			{
				pthread_mutex_lock(&gl.print);
				printf("%ld philosopher %d die\n", timepassed(gl.start), i + 1);
				k = 0;
				break ;
			}
			i++;
		}
	}
	return (0);
}

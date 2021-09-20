#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>



typedef struct philo{
    int     nphilos;
    int     numofphilo;
    int     timetodie;
    int     timetoeat;
    int     timetosleep;
    pthread_mutex_t *forks;
    int     index;
}               t_philo;



#endif

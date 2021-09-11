#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

pthread_mutex_t *forks;

typedef struct philo{
    int     nphilos;
}               t_philo;



#endif
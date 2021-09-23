#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct  data{
    int         pid;
    struct timeval start;
    struct timeval end;
    int     timetoeat;
} t_data;

typedef struct philo{
    int     numofphilo;
    int     timetodie;
    int     timetoeat;
    int     timetosleep;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int     index;
    int     reminder;
    t_data  *dl;
}               t_philo;



#endif

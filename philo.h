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
    int     timesme;
    int     timesme2;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    int     index;
    int     reminder;
    long int    start;
    int     *tab;
    t_data  *dl;
}               t_philo;



#endif

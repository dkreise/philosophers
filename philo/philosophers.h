#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
// libft

typedef struct s_philo
{
    int id;
    int philo_cnt;
    int death_time;
    int eat_time;
    int sleep_time;
    int eat_cnt;
    int cnt_eaten;
    int time_of_death;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data;
}   t_philo;

typedef struct s_data
{
    int philo_cnt;
    int death_time;
    int eat_time;
    int sleep_time;
    int eat_cnt;
    int end_flg;
    int full_philos;
    pthread_mutex_t *forks;
    struct s_philo *philos;
    pthread_t *threads;
} t_data;

void init_data(t_data *data, int argc, char **argv);
void *routine(void *arg_philo);
int cur_time_ms(void);
int ft_usleep(int ms);

#endif

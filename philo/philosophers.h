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
    pthread_mutex_t death_mutex;
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
    int start_time;
    pthread_mutex_t *forks;
    struct s_philo *philos;
    pthread_t *threads;
    pthread_mutex_t print_mutex;
    pthread_mutex_t end_mutex;
    pthread_mutex_t full_mutex;
} t_data;

void init_data(t_data *data, int argc, char **argv);
void *routine(void *arg_philo);
void monitor(t_data *data);
int cur_time_ms(void);
int ft_usleep(int ms);

#endif

#include "philosophers.h"

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printf("%i has taken a left fork\n", philo->id);
    pthread_mutex_lock(philo->right_fork);
    printf("%i has taken a right fork\n", philo->id);
    printf("%i is eating\n", philo->id);
    ft_usleep(philo->eat_time);
    philo->time_of_death = cur_time_ms() + philo->death_time;
    philo->cnt_eaten = philo->cnt_eaten + 1;
    pthread_mutex_unlock(philo->left_fork);
    printf("%i has unlocked a left fork\n", philo->id);
    pthread_mutex_unlock(philo->right_fork);
    printf("%i has unlocked a right fork\n", philo->id);
}

// eat, sleep, think
void *routine(void *arg_philo)
{
    t_philo *philo;

    philo = (t_philo *) arg_philo;
    printf("--- in thread of philo %i ---\n", philo->id);
    philo->time_of_death = cur_time_ms() + philo->death_time;
    // while dead_flg == 0 ??
    while (philo->cnt_eaten < philo->eat_cnt)
    {
        if (philo->id % 2 == 1)
            ft_usleep(100);
        eat(philo);
        printf("%i is sleeping\n", philo->id);
        ft_usleep(philo->sleep_time);
        printf("%i is thinking\n", philo->id);
    }
    return (NULL); // how to avoid it or not
}

void monitor(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_cnt)
    {
        if (data->philos[i].time_of_death > 0 && cur_time_ms() > data->philos[i].time_of_death)
        {
            printf("%i is dead\n", data->philos[i].id);
            data->end_flg = 1;
            break ;
        }
        if (data->eat_cnt >= 0  && data->philos[i].cnt_eaten == data->eat_cnt)
            data->full_philos = data->full_philos + 1;
        if (data->eat_cnt >= 0 && data->full_philos == data->philo_cnt)
        {
            data->end_flg = 1;
            break;
        }
        i ++;
        if (i == data->philo_cnt)
            i = 0;
    }
}
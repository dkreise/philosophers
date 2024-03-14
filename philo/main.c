#include "philosophers.h"

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_cnt)
    {
        // protect thread joins
        pthread_join(data->threads[i], NULL);
        i ++;
    }
}

void destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_cnt)
    {
        pthread_mutex_destroy(&(data->forks[i]));
        pthread_mutex_destroy(&(data->philos[i].death_mutex));
        i ++;
    }
    pthread_mutex_destroy(&(data->full_mutex));
    pthread_mutex_destroy(&(data->print_mutex));
    pthread_mutex_destroy(&(data->end_mutex));
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("Invalid number of arguments\n");
        // print smth better
        return (1);
    }
    // check that args are numbers
    init_data(&data, argc, argv);
    monitor(&data);
    join_threads(&data);
    destroy_mutex(&data);
    return (0);
}
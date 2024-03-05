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
        i ++;
    }
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
    //printf("philo cnt: %i\n", data.philo_cnt);
    //printf("id and meals eaten: %i, %i\n", data.philos[1].id, data.philos[1].cnt_eaten);
    join_threads(&data);
    destroy_mutex(&data);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:06:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/15 15:28:09 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    if (invalid_args(argc, argv))
        return (1);
    init_data(&data, argc, argv);
    if (data.philo_cnt == 0)
        return (0);
    monitor(&data);
    join_threads(&data);
    destroy_mutex(&data);
    return (0);
}

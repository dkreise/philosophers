/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:06:27 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/15 16:56:51 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_cnt)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (1);
		i ++;
	}
	return (0);
}

void	destroy_mutex(t_data *data)
{
	int	i;

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

void	free_data(t_data *data)
{
	if (data->forks)
		free((data->forks));
	if (data->philos)
		free((data->philos));
	if (data->threads)
		free((data->threads));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (invalid_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) != 0)
	{
		free_data(&data);
		return (1);
	}
	if (data.philo_cnt == 0)
		return (0);
	monitor(&data);
	if (join_threads(&data) != 0)
	{
		printf("Error: join_threads error\n");
		free_data(&data);
		return (1);
	}
	destroy_mutex(&data);
	free_data(&data);
	return (0);
}

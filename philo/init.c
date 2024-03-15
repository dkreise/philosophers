/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:06:12 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/15 16:56:47 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_cnt)
	{
		if (pthread_create(&(data->threads[i]), NULL, &routine,
				&(data->philos[i])) != 0)
			return (1);
		i ++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_cnt)
	{
		data->philos[i].id = i + 1;
		data->philos[i].philo_cnt = data->philo_cnt;
		data->philos[i].death_time = data->death_time;
		data->philos[i].eat_time = data->eat_time;
		data->philos[i].sleep_time = data->sleep_time;
		data->philos[i].eat_cnt = data->eat_cnt;
		data->philos[i].cnt_eaten = 0;
		data->philos[i].time_of_death = -1;
		data->philos[i].left_fork = &(data->forks[i]);
		if (i == 0)
			data->philos[i].right_fork = &(data->forks[data->philo_cnt - 1]);
		else
			data->philos[i].right_fork = &(data->forks[i - 1]);
		pthread_mutex_init(&(data->philos[i].death_mutex), NULL);
		data->philos[i].data = data;
		i ++;
	}
	data->start_time = cur_time_ms();
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_cnt)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i ++;
	}
	pthread_mutex_init(&(data->print_mutex), NULL);
	pthread_mutex_init(&(data->full_mutex), NULL);
	pthread_mutex_init(&(data->end_mutex), NULL);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_cnt = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->eat_cnt = -1;
	if (argc == 6)
		data->eat_cnt = ft_atoi(argv[5]);
	data->end_flg = 0;
	data->full_philos = 0;
	data->forks = malloc(data->philo_cnt * sizeof(pthread_mutex_t));
	data->philos = malloc(data->philo_cnt * sizeof(t_philo));
	data->threads = malloc(data->philo_cnt * sizeof(pthread_t));
	if (!data->forks || !data->philos || !data->threads)
	{
		printf("Error: malloc error\n");
		return (1);
	}
	init_mutex(data);
	init_philos(data);
	if (init_threads(data) != 0)
	{
		printf("Error: init_threads error\n");
		return (1);
	}
	return (0);
}

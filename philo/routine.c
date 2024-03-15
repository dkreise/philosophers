/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:06:36 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/15 17:14:50 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->philo_cnt == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken left fork");
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken left fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken right fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&(philo->death_mutex));
	philo->time_of_death = cur_time_ms() + philo->death_time;
	pthread_mutex_unlock(&(philo->death_mutex));
	ft_usleep(philo->eat_time);
	philo->cnt_eaten = philo->cnt_eaten + 1;
	if (philo->eat_cnt >= 0 && philo->cnt_eaten == philo->eat_cnt)
	{
		pthread_mutex_lock(&(philo->data->full_mutex));
		philo->data->full_philos = philo->data->full_philos + 1;
		pthread_mutex_unlock(&(philo->data->full_mutex));
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg_philo)
{
	t_philo	*philo;
	int		end;

	philo = (t_philo *) arg_philo;
	end = 0;
	pthread_mutex_lock(&(philo->death_mutex));
	philo->time_of_death = cur_time_ms() + philo->death_time;
	pthread_mutex_unlock(&(philo->death_mutex));
	if (one_philo(philo))
		return (NULL);
	if (philo->id % 2 == 1)
		ft_usleep(philo->eat_time / 2);
	while (end == 0)
	{
		eat(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->sleep_time);
		print_state(philo, "is thinking");
		pthread_mutex_lock(&(philo->data->end_mutex));
		end = philo->data->end_flg;
		pthread_mutex_unlock(&(philo->data->end_mutex));
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int	i;
	int	death_time;

	i = 0;
	while (1)
	{
		if (i == data->philo_cnt)
			i = 0;
		pthread_mutex_lock(&(data->philos[i].death_mutex));
		death_time = data->philos[i].time_of_death;
		pthread_mutex_unlock(&(data->philos[i].death_mutex));
		if (death_time > 0 && cur_time_ms() > death_time)
		{
			print_end(data, DIED, i);
			break ;
		}
		if ((data->eat_cnt >= 0 && full_philos(data) == data->philo_cnt)
			|| data->eat_cnt == 0)
		{
			print_end(data, FULL, i);
			break ;
		}
		i ++;
	}
}

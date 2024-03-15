/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:06:46 by dkreise           #+#    #+#             */
/*   Updated: 2024/03/15 15:19:20 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_state(t_philo *philo, char *state)
{
    int end;

    pthread_mutex_lock(&(philo->data->end_mutex));
    end = philo->data->end_flg;
    pthread_mutex_lock(&(philo->data->print_mutex));
    if (end == 0)
        printf("%i %i %s\n", cur_time_ms() - philo->data->start_time, philo->id, state);
    pthread_mutex_unlock(&(philo->data->end_mutex));
    pthread_mutex_unlock(&(philo->data->print_mutex));
}

int ft_atoi(char *nptr)
{
    long int    n;

    n = 0;
    while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\r'
        || *nptr == '\f' || *nptr == '\v')
        nptr ++;
    if (*nptr == '+')
        nptr ++;
    if (*nptr == '\0')
        return (-1);
    while (*nptr != '\0')
    {
        if (*nptr >= '0' && *nptr <= '9')
            n = n * 10 + (*nptr - 48);
        else
            return (-1);
        if (n > INT_MAX)
            return (-1);
        nptr ++;
    }
    return (n);
}

int invalid_args(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Invalid number of arguments\nPut 4 or 5 arguments:\n");
        printf("1. number of philosophers\n");
        printf("2. time to die (in milliseconds)\n");
        printf("3. time to eat (in milliseconds)\n");
        printf("4. time to sleep (in milliseconds)\n");
        printf("5. (optional) number of times each philosopher must eat\n");
        return (1);
    }
    i = 1;
    while (i < argc)
    {
        if (ft_atoi(argv[i]) == -1)
        {
            printf("Invalid arguments\nPut only integers\n");
            return(1);
        }
        i ++;
    }
    return (0);
}

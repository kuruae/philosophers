/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:23 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/30 16:26:52 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]) == 1)
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

t_error	init_data(t_data *data, t_philo *philo, char **argv, int argc)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->maximum_meal = ft_atoi(argv[5]);
	while (i != data->nb_philo)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].meal_remaining = data->maximum_meal;
		philo[i].last_eaten = 0;
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[i - 1];
		if (pthread_mutex_init(&philo[i].right_fork, NULL) != 0)
			return (ERR_MALLOC);
		if (i != 0)
			philo[i].left_fork = &data->forks[i - 1];
		i++;
	}
	return (SUCCESS);
}

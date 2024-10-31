/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:23 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/31 16:28:36 by emagnani         ###   ########.fr       */
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

static t_error	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].data = data;
		philo[i].meal_remaining = data->maximum_meal;
		philo[i].last_eaten = 0;
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[i - 1];
		if (pthread_mutex_init(philo[i].right_fork, NULL) != 0)
			return (ERR_MALLOC);
		if (i != 0)
			philo[i].left_fork = philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = philo[data->nb_philo - 1].right_fork;
	return (SUCCESS);
}

static t_error	init_data(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_time();
	if (argc == 6)
		data->maximum_meal = ft_atoi(argv[5]);
	return (SUCCESS);
}

t_error	init_all(t_data *data, t_philo *philo, char **argv, int argc)
{
	if (init_data(data, argv, argc) != SUCCESS)
		return (ERR_MALLOC);
	if (init_philo(philo, data) != SUCCESS)
		return (ERR_MALLOC);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:23 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/09 22:42:45 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_error	init_mutexes_data(t_data *data)
{
	int	i;

	i = 0;
	// Initialize each fork's mutex
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	i = 0;
	// Initialize the log mutex
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (ERR_MALLOC);

	// Initialize the end mutex
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
		return (ERR_MALLOC);

	return (SUCCESS);
}

static t_error	init_mutexes_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 200)
	{
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL) != 0)
			return (ERR_MALLOC);
		if (pthread_mutex_init(&philo[i].flag, NULL) != 0)
			return (ERR_MALLOC);
		i++;
	}
	return (SUCCESS);
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
		philo[i].left_fork = &(data->forks[i]);
		philo[i].right_fork = &(data->forks[(i + 1) % data->nb_philo]);
		i++;
	}
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
	if (data->nb_philo == 1)
	{
		printf("0 :1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%lld :1 died\n", get_time() - data->start_time);
		exit_err(ERR_DEATH);
	}
	if (init_mutexes_data(data) != SUCCESS)
		return (ERR_MALLOC);
	if (init_philo(philo, data) != SUCCESS)
		return (ERR_MALLOC);
	if (init_mutexes_philo(philo) != SUCCESS)
		return (ERR_MALLOC);
	return (SUCCESS);
}

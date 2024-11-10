/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:55:23 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 18:15:06 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		philo[i].state = DEFAULT;
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
	data->should_end = 0;
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

t_error	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i != data->nb_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]) != 0)
			return (FAILURE);
		i++;
	}
	monitoring(data, philo);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			return (FAILURE);
		i++;
	}
	destroy_mutexes(data, philo);
	return (SUCCESS);
}

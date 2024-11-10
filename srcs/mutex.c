/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:39:28 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 04:27:08 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	init_mutexes_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (0);
		i++;
	}
	i = 0;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (ERR_MALLOC);
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_error	init_mutexes_philo(t_philo *philo)
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

t_error	destroy_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			return (ERR_MALLOC);
		i++;
	}
	i = 0;
	if (pthread_mutex_destroy(&data->log_mutex) != 0)
		return (ERR_MALLOC);
	if (pthread_mutex_destroy(&data->end_mutex) != 0)
		return (ERR_MALLOC);
	i = 0;
	while (i < 200)
	{
		if (pthread_mutex_destroy(&philo[i].meal_mutex) != 0)
			return (ERR_MALLOC);
		if (pthread_mutex_destroy(&philo[i].flag) != 0)
			return (ERR_MALLOC);
		i++;
	}
	return (SUCCESS);
}

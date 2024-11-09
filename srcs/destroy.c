/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:39:28 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/09 17:43:44 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
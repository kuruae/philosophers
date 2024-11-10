/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:55:16 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 20:03:06 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	monitoring(t_data *data, t_philo *philo)
{
	int i;
	long current_time;
	int all_ate_enough;

	while (1)
	{
		i = 0;
		all_ate_enough = 1;
		
		while (i < data->nb_philo)
		{
			current_time = get_time() - data->start_time;
			
			pthread_mutex_lock(&philo[i].meal_mutex);
			if ((current_time - philo[i].last_eaten) > data->time_to_die)
			{
				pthread_mutex_lock(&philo[i].flag);
				pthread_mutex_lock(&data->end_mutex);
				philo[i].state = DIED;
				printf(COLOR_RED "%ld :%d died\n" COLOR_RESET, current_time, philo[i].id);
				data->should_end = 1;
				pthread_mutex_unlock(&data->end_mutex);
				pthread_mutex_unlock(&philo[i].flag);
				pthread_mutex_unlock(&philo[i].meal_mutex);
				return (ERR_DEATH);
			}

			if (data->maximum_meal > 0 && philo[i].meal_remaining > 0)
				all_ate_enough = 0;

			pthread_mutex_unlock(&philo[i].meal_mutex);
			i++;
		}
		if (data->maximum_meal > 0 && all_ate_enough)
		{
			pthread_mutex_lock(&data->end_mutex);
			data->should_end = 1;
			data->all_satisfied = 1;
			pthread_mutex_unlock(&data->end_mutex);
			return (SUCCESS);
		}
		usleep(100);
	}
	return (FAILURE);
}

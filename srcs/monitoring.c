/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:55:16 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/12 14:35:33 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	safe_print_monitor(t_data *data, char *msg, int philo_id)
{
	printf("%lld :%d %s\n", get_time() - data->start_time, philo_id, msg);
}

static t_error	philo_dies(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].flag);
	pthread_mutex_lock(&data->end_mutex);
	philo[i].state = DIED;
	safe_print_monitor(data, COLOR_RED "died", philo[i].id);
	data->should_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
	pthread_mutex_unlock(&philo[i].flag);
	pthread_mutex_unlock(&philo[i].meal_mutex);
	return (ERR_DEATH);
}

static t_error	philo_are_satisfied(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->should_end = 1;
	data->all_satisfied = 1;
	pthread_mutex_unlock(&data->end_mutex);
	return (SUCCESS);
}

t_error	monitoring(t_data *data, t_philo *philo)
{
	int		i;
	int		all_ate_enough;
	long	current_time;

	while (1)
	{
		i = 0;
		all_ate_enough = 1;
		while (i < data->nb_philo)
		{
			current_time = get_time() - data->start_time;
			pthread_mutex_lock(&philo[i].meal_mutex);
			if ((current_time - philo[i].last_eaten) > data->time_to_die)
				return (philo_dies(data, philo, i));
			if (data->maximum_meal > 0 && philo[i].meal_remaining > 0)
				all_ate_enough = 0;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			i++;
		}
		if (data->maximum_meal > 0 && all_ate_enough)
			return (philo_are_satisfied(data));
		usleep(100);
	}
	return (FAILURE);
}

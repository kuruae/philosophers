/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:55:00 by enzo              #+#    #+#             */
/*   Updated: 2024/11/10 01:38:18 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}

t_error check_if_someone_died(t_data *data, t_philo *philo, t_action state)
{
	pthread_mutex_lock(&philo->flag);
	pthread_mutex_lock(&data->end_mutex);	
	if (philo->state == DIED || data->should_end == 1)
	{
		pthread_mutex_unlock(&data->end_mutex);
		pthread_mutex_unlock(&philo->flag);
		return (ERR_DEATH);
	}
	philo->state = state;
	pthread_mutex_unlock(&data->end_mutex);
	pthread_mutex_unlock(&philo->flag);
	return (SUCCESS);
}

t_error sleep_action(long long desired_time, t_data *data, t_philo *philo, t_action state)
{
	long long	time;

	time = get_time() - data->start_time;
	desired_time += time;
	while (time < desired_time)
	{
		usleep(50);
		time = get_time() - data->start_time;
		if (state != EAT && check_if_someone_died(data, philo, state) != SUCCESS)
			return (ERR_DEATH);
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:04:45 by enzo              #+#    #+#             */
/*   Updated: 2024/11/09 16:58:04 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_error check_if_someone_died(t_data *data, t_philo *philo, t_action state)
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

t_error	thinking(t_data *data, t_philo *philo)
{
	long			time;

	if (check_if_someone_died(data, philo, THINK) != SUCCESS)
		return (ERR_DEATH);
	time = get_time() - data->start_time;
	printf("%ld :%d is thinking\n", time, philo->id);
	return (SUCCESS);
}

t_error	sleeping(t_data *data, t_philo *philo)
{
	long			time;

	if (check_if_someone_died(data, philo, SLEEP) != SUCCESS)
		return (ERR_DEATH);
	time = get_time() - data->start_time;
	printf("%ld :%d is sleeping\n", time, philo->id);
	if (sleep_action(data->time_to_sleep, data, philo) != SUCCESS)
		return (ERR_DEATH);
	return (SUCCESS);
}


t_error	eating(t_data *data, t_philo *philo)
{
	long	time;

	if (check_if_someone_died(data, philo, EAT) != SUCCESS)
		return (ERR_DEATH);

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	
	time = get_time() - data->start_time;
	
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eaten = get_time() - data->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d is eating\n", time, philo->id);
	
	usleep(data->time_to_eat * 1000);
	
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meal_remaining > 0)
		philo->meal_remaining--;
	pthread_mutex_unlock(&philo->meal_mutex);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (SUCCESS);
}

t_error sleep_action(long long desired_time, t_data *data, t_philo *philo)
{
	long long	time;

	time = get_time() - data->start_time;
	desired_time += time;

	while (time < desired_time)
	{
		usleep(50);
		time = get_time() - data->start_time;
		if (check_if_someone_died(data, philo, SLEEP) != SUCCESS)
			return (ERR_DEATH);
	}
	return (SUCCESS);
}

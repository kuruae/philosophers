/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:04:45 by enzo              #+#    #+#             */
/*   Updated: 2024/11/05 22:09:00 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	thinking(t_data *data, t_philo *philo)
{
	long			time;

    pthread_mutex_lock(philo->flag);
    if (philo->state == DIED)
        return (ERR_DEATH);
    pthread_mutex_unlock(philo->flag);
	time = get_time() - data->start_time;
	printf("%ld :%d is thinking\n", time, philo->id);
	return (SUCCESS);
}

t_error	sleeping(t_data *data, t_philo *philo)
{
	long			time;

	time = get_time() - data->start_time;
    pthread_mutex_lock(philo->flag);
    if (philo->state == DIED)
        return (ERR_DEATH);
    pthread_mutex_unlock(philo->flag);
	printf("%ld :%d is sleeping\n", time, philo->id);
	if (sleep_action(data->time_to_sleep, data, philo) != SUCCESS)
		printf("%ld :%d bro died\n", time, philo->id);
	return (SUCCESS);
}

t_error	eating(t_data *data, t_philo *philo)
{
	long	time;

	time = get_time() - data->start_time;
	pthread_mutex_lock(philo->flag);
	if (philo->state == DIED)
	{
		printf("%ld :%d bro died\n", time, philo->id);
		return (ERR_DEATH);
	}
	pthread_mutex_unlock(philo->flag);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	
	pthread_mutex_lock(&philo->meal_mutex);
	pthread_mutex_lock(philo->flag);
	philo->state = EAT;
	philo->last_eaten = get_time() - data->start_time;
	pthread_mutex_unlock(philo->flag);
	pthread_mutex_unlock(&philo->meal_mutex);
	
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d is eating\n", time, philo->id);
	if (sleep_action(data->time_to_eat, data, philo) != SUCCESS)
	{
		printf("%ld :%d bro died\n", time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (ERR_DEATH);
	}

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
	t_action	current_state;

	time = get_time() - data->start_time;
	desired_time += time;

	while (time < desired_time)
	{
		usleep(50);
		time = get_time() - data->start_time;

		pthread_mutex_lock(philo->flag);
		current_state = philo->state;
		pthread_mutex_unlock(philo->flag);

		if (current_state == DIED)
			return (FAILURE);
	}
	return (SUCCESS);
}

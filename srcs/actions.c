/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:04:45 by enzo              #+#    #+#             */
/*   Updated: 2024/11/12 14:13:41 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_error	thinking(t_data *data, t_philo *philo)
{
	if (safe_print(data, "is thinking", philo, THINK) != SUCCESS)
		return (ERR_DEATH);
	return (SUCCESS);
}

static t_error	sleeping(t_data *data, t_philo *philo)
{
	if (safe_print(data, "is sleeping", philo, SLEEP) != SUCCESS)
		return (ERR_DEATH);
	if (sleep_action(data->time_to_sleep, data, philo, SLEEP) != SUCCESS)
		return (ERR_DEATH);
	return (SUCCESS);
}

static t_error	eating(t_data *data, t_philo *philo)
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;

	first_fork = ft_first_fork(philo);
	second_fork = ft_second_fork(philo);
	lock_forks(first_fork, second_fork);
	if (print_eating(data, philo) != SUCCESS)
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (ERR_DEATH);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eaten = get_time() - data->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	sleep_action(data->time_to_eat, data, philo, EAT);
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meal_remaining > 0)
		philo->meal_remaining--;
	pthread_mutex_unlock(&philo->meal_mutex);
	unlock_forks(first_fork, second_fork);
	return (SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->flag);
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->should_end || philo->state == DIED)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			pthread_mutex_unlock(&philo->flag);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_unlock(&philo->flag);
		if (eating(philo->data, philo) != SUCCESS)
			break ;
		if (sleeping(philo->data, philo) != SUCCESS)
			break ;
		if (thinking(philo->data, philo) != SUCCESS)
			break ;
	}
	return (NULL);
}

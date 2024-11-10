/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:04:45 by enzo              #+#    #+#             */
/*   Updated: 2024/11/10 19:21:42 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_error	thinking(t_data *data, t_philo *philo)
{
	long	time;

	if (check_if_someone_died(data, philo, THINK) != SUCCESS)
		return (ERR_DEATH);
	time = get_time() - data->start_time;
	printf("%ld :%d is thinking\n", time, philo->id);
	return (SUCCESS);
}

static t_error	sleeping(t_data *data, t_philo *philo)
{
	long			time;

	if (check_if_someone_died(data, philo, SLEEP) != SUCCESS)
		return (ERR_DEATH);
	time = get_time() - data->start_time;
	printf("%ld :%d is sleeping\n", time, philo->id);
	if (sleep_action(data->time_to_sleep, data, philo, SLEEP) != SUCCESS)
		return (ERR_DEATH);
	return (SUCCESS);
}

static t_error	eating(t_data *data, t_philo *philo)
{
    long	time;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // Determine fork order based on fork numbers to prevent deadlock
    if (philo->id == data->nb_philo)  // Last philosopher
    {
        first_fork = philo->right_fork;  // Lower number
        second_fork = philo->left_fork;  // Higher number
    }
    else
    {
        first_fork = philo->left_fork;   // Lower number
        second_fork = philo->right_fork; // Higher number
    }

    pthread_mutex_lock(first_fork);
    pthread_mutex_lock(second_fork);

    if (check_if_someone_died(data, philo, EAT) != SUCCESS)
    {
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        return (ERR_DEATH);
    }
    time = get_time() - data->start_time;
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_eaten = get_time() - data->start_time;
    pthread_mutex_unlock(&philo->meal_mutex);
    printf("%ld :%d has taken a fork\n", time, philo->id);
    printf("%ld :%d has taken a fork\n", time, philo->id);
    printf("%ld :%d is eating\n", time, philo->id);
    sleep_action(data->time_to_eat, data, philo, EAT);
    pthread_mutex_lock(&philo->meal_mutex);
    if (philo->meal_remaining > 0)
        philo->meal_remaining--;
    pthread_mutex_unlock(&philo->meal_mutex);
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
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

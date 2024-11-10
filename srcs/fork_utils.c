/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:19:54 by enzo              #+#    #+#             */
/*   Updated: 2024/11/11 00:24:49 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mutex	*ft_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(100);
		return (philo->right_fork);
	}
	else
		return (philo->left_fork);
}

t_mutex	*ft_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(100);
		return (philo->left_fork);
	}
	else
		return (philo->right_fork);
}

void	lock_forks(t_mutex *first_fork, t_mutex *second_fork)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(second_fork);
}

void	unlock_forks(t_mutex *first_fork, t_mutex *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

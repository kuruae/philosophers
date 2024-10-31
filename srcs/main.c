/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/31 18:53:52 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(void)
{
	write(2, "parsing error\n", 15);
	exit(EXIT_FAILURE);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(50);
	eating(philo->data, philo);
	sleeping(philo->data, philo);
	thinking(philo->data, philo);
	return (NULL);
}

t_error	thinking(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	// pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(philo->right_fork);
	philo->state = THINK;
	gettimeofday(&tv, NULL);
	time = get_time() - data->start_time;
	printf("%ld :%d is thinking\n", time, philo->id);
	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);
	return (SUCCESS);
}

t_error	sleeping(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	// pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(philo->right_fork);
	philo->state = SLEEP;
	gettimeofday(&tv, NULL);
	time = get_time() - data->start_time;
	printf("%ld :%d is sleeping\n", time, philo->id);
	if (sleep_action(data->time_to_sleep, data, philo) != SUCCESS)
		printf("bro died\n");
	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);
	return (SUCCESS);
}

t_error	sleep_action(long long desired_time, t_data *data, t_philo *philo)
{
	long long	time;

	time = get_time() - data->start_time;
	desired_time += time;
	while (time < desired_time)
	{
		usleep(50);
		time = get_time() - data->start_time;
		if (philo->state == DIED)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_error	eating(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->flag);
	philo->state = EAT;
	gettimeofday(&tv, NULL);
	time = get_time() - data->start_time;
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d is eating\n", time, philo->id);
	if (sleep_action(data->time_to_eat, data, philo) != SUCCESS)
		return (FAILURE);
	pthread_mutex_unlock(philo->flag);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (SUCCESS);
}

t_error	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i != data->nb_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]) != 0)
			return (FAILURE);
		i++;
	}
	monitoring(data, philo);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv) == FAILURE)
		exit_err();
	if (init_all(&data, data.philo, argv, argc) != SUCCESS)
		exit_err();
	create_threads(&data, data.philo);
	// free_data_exit(&data);
	return (0);
}

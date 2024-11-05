/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/05 22:37:31 by enzo             ###   ########.fr       */
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
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->should_end || philo->state == DIED)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->end_mutex);

		if (eating(philo->data, philo) != SUCCESS)
			break;
		if (sleeping(philo->data, philo) != SUCCESS)
			break;
		if (thinking(philo->data, philo) != SUCCESS)
			break;
	}
	return (NULL);
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

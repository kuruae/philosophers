/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/05 18:23:04 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(void)
{
	write(2, "parsing error\n", 15);
	exit(EXIT_FAILURE);
}

void *routine(void *arg)
{
	t_philo *philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = philo->data;

	if (philo->id % 2 == 1)
		usleep(50);

	while (1)
	{
		pthread_mutex_lock(&data->end_mutex);
		if (data->should_end)
		{
			pthread_mutex_unlock(&data->end_mutex);
			break;
		}
		pthread_mutex_unlock(&data->end_mutex);

		if (eating(data, philo) != SUCCESS)
			break;
		if (sleeping(data, philo) != SUCCESS)
			break;
		if (thinking(data, philo) != SUCCESS)
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

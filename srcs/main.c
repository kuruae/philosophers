/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/30 23:22:54 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(void)
{
	write(2, "parsing error\n", 15);
	exit(EXIT_FAILURE);
}

static void	free_data_exit(t_data *data)
{
	(void)data;
	return ;
}

void	*routine(void *arg)
{
	t_philo *philo;
	// t_data	*data;

	philo = (t_philo*)arg;
	// data = philo->data;
	if (philo->id % 2 == 1)
		sleep(5);
	// eat(philo->data, philo);
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
	if (init_data(&data, &data.philo, argv, argc) != SUCCESS)
		exit_err();
	create_threads(&data, &data.philo);
	// free_data_exit(&data);
	return (0);
}

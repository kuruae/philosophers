/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 01:31:00 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	destroy_mutexes(data, philo);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(argc, argv) != SUCCESS)
		exit_err(ERR_BAD_ARGUMENTS);
	if (init_all(&data, data.philo, argv, argc) != SUCCESS)
		exit_err(ERR_MALLOC);
	create_threads(&data, data.philo);
	if (data.all_satisfied)
		printf(COLOR_GREEN "All philosophers are satisfied\n" COLOR_RESET);
	else 
		exit_err(ERR_DEATH);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/09 22:56:07 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(t_error error)
{
	if (error == ERR_MALLOC)
		write(2, "Error: malloc failed\n", 22);
	else if (error == ERR_DEATH)
		write(2, "A philosopher died\n", 20);
	else if (error == ERR_VALUES_TOO_LOW)
		write(2, "Error: values must be greater than 0\n", 38);
	else if (error == ERR_TOO_MANY_PHILOS)
		write(2, "Error: too many philosophers\n", 30);
	else if (error == ERR_BAD_ARGUMENTS)
		write(2, "Error: wrong arguments\n", 24);
	exit(EXIT_FAILURE);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		pthread_mutex_lock(&philo->flag);
		if (philo->data->should_end || philo->state == DIED)
		{
			pthread_mutex_unlock(&philo->data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->flag);
		pthread_mutex_unlock(&philo->data->end_mutex);

		if (eating(philo->data, philo) != SUCCESS)
			break ;
		if (sleeping(philo->data, philo) != SUCCESS)
			break ;
		if (thinking(philo->data, philo) != SUCCESS)
			break ;
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
	// free_data_exit(&data);
	return (0);
}

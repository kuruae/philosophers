/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:55:16 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/31 18:06:20 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_error	monitoring(t_data *data, t_philo *philo)
{
	int		i;
	long	time;

	i = 0;
	time = get_time() - data->start_time;
	while (1)
	{
		while (i < data->nb_philo)
		{
			if (philo[i].meal_remaining == 0)
				philo[i].state = SATISFIED;
			if ()
			{
				philo[i].state = DIED;
				printf("&ld :%d has died\n", time, philo[i].id);
			}
			i++;
		}
		i = 0;
	}
	return (SUCCESS);
}

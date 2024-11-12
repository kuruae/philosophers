/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:26:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/12 14:35:39 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(t_error error)
{
	if (error == ERR_MALLOC)
		write(2, COLOR_RED "Error: malloc failed", 25);
	else if (error == ERR_DEATH)
		write(2, "A philosopher died", 19);
	else if (error == ERR_VALUES_TOO_LOW)
		write(2, COLOR_RED "Error: values must be greater than 0", 41);
	else if (error == ERR_TOO_MANY_PHILOS)
		write(2, COLOR_RED "Error: too many philosophers", 33);
	else if (error == ERR_BAD_ARGUMENTS)
		write(2, COLOR_RED "Error: wrong arguments", 27);
	write(2, COLOR_RESET "\n", 5);
	exit(EXIT_FAILURE);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]) == 1)
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

t_error	safe_print(t_data *data, char *msg, t_philo *philo, t_action state)
{
	pthread_mutex_lock(&data->log_mutex);
	if (check_if_someone_died(data, philo, state) != SUCCESS)
	{
		pthread_mutex_unlock(&data->log_mutex);
		return (ERR_DEATH);
	}
	printf("%lld :%d %s\n", get_time() - data->start_time, philo->id, msg);
	pthread_mutex_unlock(&data->log_mutex);
	return (SUCCESS);
}

t_error	print_eating(t_data *data, t_philo *philo)
{
	if (safe_print(data, "has taken a fork", philo, EAT) != SUCCESS)
		return (ERR_DEATH);
	if (safe_print(data, "has taken a fork", philo, EAT) != SUCCESS)
		return (ERR_DEATH);
	if (safe_print(data, "is eating", philo, EAT) != SUCCESS)
		return (ERR_DEATH);
	return (SUCCESS);
}

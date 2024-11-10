/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:26:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 01:44:36 by enzo             ###   ########.fr       */
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
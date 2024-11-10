/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:41 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 01:18:27 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static bool	ft_str_isdigit(char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	check_values(char **argv)
{
	int	failure;

	failure = 0;
	if (ft_atoi(argv[1]) > 200)
		exit_err(ERR_TOO_MANY_PHILOS);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		failure = 1;
	if (argv[5] && ft_atoi(argv[5]) < 1)
		failure = 1;
	if (failure == 1)
		exit_err(ERR_VALUES_TOO_LOW);
}

t_error	parsing(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (FAILURE);
	i = 1;
	while (argv[i])
	{
		if (ft_str_isdigit(argv[i]) == false)
			return (FAILURE);
		i++;
	}
	check_values(argv);
	return (SUCCESS);
}

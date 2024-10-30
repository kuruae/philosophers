/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:41 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/30 22:50:21 by emagnani         ###   ########.fr       */
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
	return (SUCCESS);
}

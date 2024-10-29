/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:41 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/29 18:15:52 by emagnani         ###   ########.fr       */
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

int	parsing(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_str_isdigit(arg[i]) == false)
			return (-1);
		i++;
	}
	return (0);
}

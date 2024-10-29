/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/29 21:16:21 by emagnani         ###   ########.fr       */
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
	free (data);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || parsing(argv) == -1)
		exit_err();
	if (init_data(&data, argv, argc) != SUCCESS)
		free_data_exit(&data);
	free_data_exit(&data);
	return (0);
}

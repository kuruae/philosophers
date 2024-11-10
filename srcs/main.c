/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:28:37 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 04:22:55 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

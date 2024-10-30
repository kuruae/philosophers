/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:09 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:37 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include "struct.h"

// STRUCTS AND ENUMS

typedef pthread_mutex_t	t_mutex;
typedef enum e_action	t_action;
typedef enum e_error	t_error;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

// FUNCTIONS 

void	exit_err(void);
int		parsing(char **arg);
int		ft_isdigit(int c);
t_error	init_data(t_data *data, t_philo *philo, char **argv, int argc);
long long	get_time(void);

#endif

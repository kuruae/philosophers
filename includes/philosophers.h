/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:09 by emagnani          #+#    #+#             */
/*   Updated: 2024/10/31 01:52:31 by enzo             ###   ########.fr       */
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

t_error		parsing(int agrc, char **argv);
t_error		init_all(t_data *data, t_philo *philo, char **argv, int argc);
t_error		create_threads(t_data *data, t_philo *philo);
void		*routine(void *arg);
void		exit_err(void);
int			eat(t_data *data, t_philo *philo);

// UTILS

long long	get_time(void);
int			ft_isdigit(int c);

#endif

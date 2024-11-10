/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:09 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/10 19:35:02 by emagnani         ###   ########.fr       */
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

// COLORS

# define COLOR_RESET "\x1b[0m"
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"

// STRUCTS AND ENUMS

typedef pthread_mutex_t	t_mutex;
typedef enum e_action	t_action;
typedef enum e_error	t_error;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

// FUNCTIONS 

void		*routine(void *arg);
t_error		parsing(int agrc, char **argv);
t_error		init_all(t_data *data, t_philo *philo, char **argv, int argc);
t_error		create_threads(t_data *data, t_philo *philo);
t_error		monitoring(t_data *data, t_philo *philo);
t_error		check_if_someone_died(t_data *data, t_philo *philo, t_action state);
t_error		sleep_action(long long desired_time, t_data *data, t_philo *philo,
				t_action state);

// MUTEXES

t_error		init_mutexes_data(t_data *data);
t_error		init_mutexes_philo(t_philo *philo);
t_error		destroy_mutexes(t_data *data, t_philo *philo);

// UTILS

long long	get_time(void);
void		safe_print(t_data *data, char *msg, int philo_id);
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
int			ft_isspace(int c);

// ERRORS

void		exit_err(t_error error);

#endif

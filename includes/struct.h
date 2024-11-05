/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:40:10 by emagnani          #+#    #+#             */
/*   Updated: 2024/11/05 17:51:37 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philosophers.h"

typedef pthread_mutex_t	t_mutex;

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED,
	SATISFIED,
}	t_action;

typedef enum e_error
{
	SUCCESS,
	ERR_MALLOC,
	ERR_DEATH,
	FAILURE
}	t_error;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meal_remaining;
	long long		last_eaten;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_mutex			meal_mutex;
	t_mutex			*flag;
	t_action		state;
	pthread_t		thread_id;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int			nb_philo;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			maximum_meal;
	long long	start_time;
	int			should_end;
	int			all_satisfied;
	int			end_reason;
	t_mutex		log_mutex;
	t_mutex		end_mutex;
	t_mutex		forks[200];
	t_philo		philo[200];
}	t_data;

#endif
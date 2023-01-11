/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:24:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 21:08:35 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_REFERENCE_H
# define MY_REFERENCE_H

# define VALID 1
# define INVALID 0
# define EXIST 1
# define NIHIL 0

# define FREE 1
# define EXTREM "2147483647"

typedef int				t_sophia;
typedef pthread_mutex_t	t_fork;

typedef struct s_philos
{
	t_sophia	death_flag;
	pthread_t	t;
}t_philos;

typedef struct s_args
{
	t_sophia	philo_num;
	t_sophia	time_to_die;
	t_sophia	time_to_eat;
	t_sophia	time_to_sleep;
	t_sophia	number_of_meals;
}t_args;

typedef struct s_global
{
	t_sophia		*curr_index;
	t_philos		*philos;
	t_fork			*forks;
	pthread_mutex_t	gp_mtx;
	t_args			args;
}t_global;

#endif
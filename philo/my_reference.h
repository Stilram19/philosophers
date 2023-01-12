/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:24:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/12 18:41:12 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_REFERENCE_H
# define MY_REFERENCE_H

# define VALID 1
# define INVALID 0
# define EXIST 1
# define NIHIL 0
# define THINKING 0
# define EATING 1
# define SLEEPING 2

# define FREE 1
# define EXTREM "2147483647"

typedef int				t_sophia;
typedef pthread_mutex_t	t_fork;

typedef struct s_philos
{
	t_sophia	id;
	t_sophia	state;
	t_fork		lf;
	t_fork		rf;
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
	t_philos		*philos;
	t_args			args;
}t_global;

#endif
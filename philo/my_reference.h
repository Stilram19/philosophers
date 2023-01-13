/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:24:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/13 22:49:41 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_REFERENCE_H
# define MY_REFERENCE_H

# define VALID 1
# define INVALID 0
# define EXIST 1
# define NIHIL 0
# define EXPIRED 0
# define THINKING 0
# define EATING 1
# define SLEEPING 2

# define EXTREM "2147483647"

typedef pthread_mutex_t	t_mtx;
typedef int				t_sophia;

typedef struct s_args
{
	t_sophia		philo_num;
	t_sophia		time_to_die;
	t_sophia		time_to_eat;
	t_sophia		time_to_sleep;
	t_sophia		number_of_meals;
	t_sophia		pass_flag;
	time_t			start_clock;
	t_mtx			pass_mtx;
	t_mtx			time_mtx;
}t_args;

typedef struct s_philos
{
	t_sophia	id;
	t_sophia	meals_count;
	time_t		timer;
	t_mtx		lf;
	t_mtx		rf;
	pthread_t	t;
	t_args		*args;
}t_philos;

#endif
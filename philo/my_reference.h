/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:24:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/02 16:34:27 by obednaou         ###   ########.fr       */
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
# define ERROR 1
# define BREAK 0
# define LOOP 1
# define DONE 1
# define SUCCESS 0
# define PSUCCESS (void *)0
# define PERROR (void *)1

# define EXTREM "2147483647"

typedef pthread_mutex_t	t_mtx;
typedef int				t_sophia;
typedef long			t_time;

typedef struct s_args
{
	t_sophia		philo_num;
	t_sophia		time_to_die;
	t_sophia		time_to_eat;
	t_sophia		time_to_sleep;
	t_sophia		number_of_meals;
	t_sophia		total_done_eating;
	t_mtx			*forks;
	t_mtx			meals_mtx;
	t_mtx			pass_mtx;
	pthread_t		supervisor;
}t_args;

typedef struct s_philos
{
	t_sophia	id;
	t_sophia	meals_count;
	t_time		timer;
	t_mtx		*lf;
	t_mtx		*rf;
	t_mtx		critical_mtx;
	pthread_t	t;
	t_args		*args;
}t_philos;

#endif

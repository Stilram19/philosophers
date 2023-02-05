/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:30:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/05 10:18:06 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_REFERENCE_BONUS_H
# define MY_REFERENCE_BONUS_H

# define NIHIL 0
# define EXIST 1
# define VALID 1
# define INVALID 0
# define ERROR 1
# define DONE 1
# define DONE_EATING_EXIT 0
# define DEATH_EXIT 2
# define EXTREM "2147483647"

typedef int		t_sophia;
typedef long	t_time;

typedef struct s_sem
{
	sem_t	*sem;
	char	*name;
}t_sem;

typedef struct s_args
{
	t_sophia	philo_num;
	t_sophia	time_to_die;
	t_sophia	time_to_eat;
	t_sophia	time_to_sleep;
	t_sophia	meals_num;
	t_sophia	eaten_meals;
	t_sophia	timer;
	t_sophia	id;
	pid_t		*pids;
	t_sem		forks;
	t_sem		print;
	t_sem		data_race;
}t_args;

#endif
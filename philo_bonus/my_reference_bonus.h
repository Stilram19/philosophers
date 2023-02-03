/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reference_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:30:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/03 18:36:17 by obednaou         ###   ########.fr       */
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
# define EXTREM "2147483647"

typedef int		t_sophia;
typedef long	t_time;

typedef struct s_args
{
	t_sophia	philo_num;
	t_sophia	time_to_die;
	t_sophia	time_to_eat;
	t_sophia	time_to_sleep;
	t_sophia	meals_num;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*print;
	sem_t		**timer_sem;
}t_args;

#endif
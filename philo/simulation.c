/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/07 10:44:21 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

t_sophia	_usleep(t_time t)
{
	t_sophia	_sleep;
	t_time		time_up;

	_sleep = 150;
	((t < 150) && (_sleep = t));
	time_up = _time() + t;
	while (_time() < time_up)
		usleep(_sleep);
	return (DONE);
}

t_sophia	create_philosophers(t_philos *p)
{
	t_sophia	i;
	t_sophia	loop;

	i = NIHIL;
	loop = LOOP;
	_time();
	while (loop)
	{
		if (pthread_create(&(p[i].t), NULL, sophia_routine, p + i)
			|| pthread_detach(p[i].t))
			return (ERROR);
		i += 2;
		(i < p->args->philo_num || (!(i % 2) && (i = (p->args->philo_num != 1))
				&& _usleep(1000)) || (loop = BREAK));
	}
	if (supervising(p))
		return (ERROR);
	return (SUCCESS);
}

t_sophia	simulation_init(t_philos *p, t_args *args)
{
	t_sophia	i;

	i = -1;
	if (pthread_mutex_init(&(args->pass_mtx), NULL)
		|| pthread_mutex_init(&(args->meals_mtx), NULL))
		return (ERROR);
	args->total_done_eating = 0;
	while (++i < args->philo_num)
	{
		p[i].id = i + 1;
		p[i].args = args;
		p[i].meals_count = 0;
		p[i].lf = args->forks + i;
		if (pthread_mutex_init(p[i].lf, NULL)
			|| pthread_mutex_init(&(p[i].critical_mtx), NULL))
			return (ERROR);
		if (!i)
			p[args->philo_num - 1].rf = p[i].lf;
		else
			p[i - 1].rf = p[i].lf;
	}
	return (SUCCESS);
}

void	clean_up(t_philos *p)
{
	t_sophia	i;

	i = -1;
	pthread_mutex_destroy(&(p->args->pass_mtx));
	pthread_mutex_destroy(&(p->args->meals_mtx));
	while (++i < p->args->philo_num)
		(pthread_mutex_destroy(p[i].lf)
			|| pthread_mutex_destroy(&(p[i].critical_mtx)));
}

t_sophia	simulation(t_args *args, t_philos **ptr_to_p)
{
	t_sophia	ret;

	if (!(args->philo_num && args->number_of_meals))
		return (SUCCESS);
	*ptr_to_p = malloc(sizeof(t_philos) * args->philo_num);
	(*ptr_to_p && (args->forks = malloc(sizeof(t_mtx) * args->philo_num)));
	ret = !(*ptr_to_p && args->forks);
	(ret || (ret = (simulation_init(*ptr_to_p, args)
				|| create_philosophers(*ptr_to_p))));
	clean_up(*ptr_to_p);
	return (ret);
}

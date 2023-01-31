/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/15 16:29:02obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

t_sophia	_usleep(t_time t)
{
	t_time	time_up;

	time_up = _time() + t;
	while (_time() < time_up)
		usleep(100);
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
		if (!(i % 2) && pthread_create(&(p[i].t), NULL, sophia_routine, p + i))
			return (ERROR);
		i += 2;
		(i < p->args->philo_num || (!(i % 2) && (i = EXIST) && _usleep(500))
			|| (loop = BREAK));
	}
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
		p[i].timer = 0;
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

void	stop_simulation(t_philos *p)
{
	t_sophia	i;

	i = -1;
	pthread_mutex_destroy(&(p->args->pass_mtx));
	while (++i < p->args->philo_num)
		(pthread_mutex_destroy(p[i].lf)
			|| pthread_mutex_destroy(&(p[i].critical_mtx)));
	if (p)
		free(p);
	if (p->args->forks)
		free(p->args->forks);
}

t_sophia	start_simulation(t_args *args)
{
	t_sophia	ret;
	t_philos	*p;

	if (!(args->philo_num))
		return (SUCCESS);
	p = malloc(sizeof(t_philos) * args->philo_num);
	(p && (args->forks = malloc(sizeof(t_mtx) * args->philo_num)));
	ret = !(p && args->forks);
	(ret || (ret = (simulation_init(p, args) || create_philosophers(p)
				|| supervising(p))));
	stop_simulation(p);
	return (ret);
}

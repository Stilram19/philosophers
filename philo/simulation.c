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
	t_sophia	_sleep;
	t_time		time_up;

	_sleep = 100;
	((t < 100) && (_sleep = t));
	time_up = _time() + t;
	while (_time() < time_up)
		usleep(_sleep);
	return (DONE);
}

void	*create_philosophers(void *args)
{
	t_sophia	i;
	t_sophia	loop;
	t_philos	*p;

	i = NIHIL;
	loop = LOOP;
	p = args;
	_time();
	while (loop)
	{
		pthread_mutex_lock(&(p->critical_mtx));
		p[i].timer = _time();
		pthread_mutex_unlock(&(p->critical_mtx));
		if (pthread_create(&(p[i].t), NULL, sophia_routine, p + i)
			|| pthread_detach(p[i].t))
			return (PERROR);
		i += 2;
		(i < p->args->philo_num || (!(i % 2) && (i = EXIST) && _usleep(1000))
			|| (loop = BREAK));
	}
	if (supervising(p))
		return (PERROR);
	return (PSUCCESS);
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

void	stop_simulation(t_philos *p)
{
	t_sophia	i;

	i = -1;
	pthread_mutex_destroy(&(p->args->pass_mtx));
	pthread_mutex_destroy(&(p->args->meals_mtx));
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
	void		*value;

	value = PSUCCESS;
	if (!(args->philo_num))
		return (SUCCESS);
	p = malloc(sizeof(t_philos) * args->philo_num);
	(p && (args->forks = malloc(sizeof(t_mtx) * args->philo_num)));
	ret = !(p && args->forks);
	(ret || (ret = (simulation_init(p, args)
				|| pthread_create(&(args->supervisor),
					NULL, create_philosophers, p)
				|| pthread_join(args->supervisor, &value)
				|| (value && (ret = ERROR)))));
	stop_simulation(p);
	return (ret);
}

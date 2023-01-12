/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/12 22:31:22 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

time_t	_time(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	*sophia(void *arg)
{
	t_philos	*p;

	p = arg;
	while (p->existence)
	{
		printf("%ld %d is thinking\n", _time(), p->id);
		pthread_mutex_lock(&(p->lf));
		printf("%ld %d has taken a fork\n", _time(), p->id);
		pthread_mutex_lock(&(p->rf));
		p->timer = _time();
		printf("%ld %d has taken a fork\n", _time(), p->id);
		printf("%ld %d is eating\n", _time(), p->id);
		pthread_mutex_unlock(&(p->rf));
		pthread_mutex_unlock(&(p->lf));
		printf("%ld %d is sleeping\n", _time(), p->id);
		usleep(p->args->time_of_sleep * 1000);
	}
}

void	create_philosophers(t_philos *p)
{
	t_sophia	i;
	t_sopiha	alive;

	i = -1;
	alive = EXIST;
	while (++i)
	{
		p[i].id = i + 1;
		p[i].args = args;
		p[i].timer = _time();
		p[i].existence = EXIST;
		if (pthread_create(&(p[i].t), NULL, sophia, &p))
			exit_with_error("Logical fallacy: failed to create philosophers");
		/*if (pthread_detach(p[i].t))
			exit_with_error("Logical fallacy: failed to detach philosophers");*/
	}
	while (alive)
	{
		i = -1;
		while (++i < p->args->philo_num)
		{
			if (_time() - p[i].timer == p->args->time_to_die)
			{
				printf("%ld %d died\n", _time(), p[i].id);
				p[i].existence = NIHIL;
				alive = NIHIL;
				break ;
			}
		}
	}
}

void	simulation_init(t_args *args)
{
	t_sophia	i;
	t_philos	*p;

	i = -1;
	p = malloc(sizeof(t_philos) * args->philo_num);
	if (!p)
		exit_with_error("Logical fallacy: can't allocate region from the heap");
	while (++i < args->philo_num)
	{
		if (pthread_mutex_init(&(p[i].lf), NULL))
			exit_with_error("Logical fallacy: Can't protect forks");
		if (!i)
			p[args->philo_num - 1].rf = p[i].lf;
		else
			p[i - 1].rf = p[i].lf;
	}
}

void	simulation_distr(t_philos *p)
{
	t_sophia	i;

	i = -1;
	while (++i < p->args->philo_num)
		pthread_mutex_destroy(&(p[i].lf));
	free(p);
}

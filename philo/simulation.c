/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/13 21:58:55 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

void	create_philosophers(t_philos *p)
{
	t_sophia	i;

	i = -1;
	while (++i)
	{
		p[i] = _time();
		if (pthread_create(&(p[i].t), NULL, sophia_routine, p + i))
			exit_with_error("Existencial crisis: failed to create philosophers");
	}
}

void	simulation_init(t_philos *p, t_args *args)
{
	t_sophia	i;

	i = -1;
	args->pass_flag = VALID;
	if (pthread_mutex_init(&(args->pass_mtx), NULL))
		exit_with_error("fallacy: Can't initialize pass mutex");
	while (++i < args->philo_num)
	{
		p[i].id = i + 1;
		p[i].args = args;
		if (pthread_mutex_init(&(p[i].lf), NULL))
			exit_with_error("fallacy: Can't protect forks");
		if (!i)
			p[args->philo_num - 1].rf = p[i].lf;
		else
			p[i - 1].rf = p[i].lf;
	}
}

void	stop_simulation(t_philos *p)
{
	t_sophia	i;

	i = -1;
	pthread_mutex_destroy(&(p->args->pass_mtx));
	while (++i < p->args->philo_num)
		pthread_mutex_destroy(&(p[i].lf));
	free(p);
}

void	start_simulation(t_args *args)
{
	t_philos	*p;

	if (!(args->philo_num - 1))
	{
		printf("%ld 1 died\n", _time() / 1000);
		exit(EXIT_SUCCESS);
	}
	p = malloc(sizeof(t_philos) * args->philo_num);
	if (!p)
		exit_with_error("fallacy: can't allocate region from the heap");
	simulation_init(p, args);
	return ;
	create_philosophers(p);
	supervising(p);
	stop_simulation(p);
}

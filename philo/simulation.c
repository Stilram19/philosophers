/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 21:12:54 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

void	*philo_routine(void *arg)
{
	t_sophia		p_num;
	static t_sophia	index;
	t_global		*g;

	g = arg;
	pthread_mutex_lock(g->gp_mtx);
	p_num = index + 1;
	pthread_mutex_unlock(g->gp_mtx);
	while (1)
	{
		pthread_mutex_lock(g->forks + p_num - 1);
		//getting the first fork
		pthread_mutex_unlock(g->forks + p_num - 1);
		pthread_mutex_lock(g->forks + p_num);
		//eating
		pthread_mutex_lock(g->forks + p_num);
		//sleeping
	}
}

void	create_philosophers(t_global *g)
{
	t_sophia	i;

	i = -1;
	while (++i)
	{
		if (pthread_create(&(g->philos[i].t), NULL, philo_routine, &g))
			exit_with_error("Logical fallacy: failed to create philosophers");
	}
}

void	simulation_init(t_global *g)
{
	t_sophia	i;

	i = -1;
	g->philos = malloc(sizeof(t_philos) * g->args.philo_num);
	g->forks = malloc(sizeof(t_fork) * g->args.philo_num);
	if (!(g->philos && g->forks))
		exit_with_error("Logical fallacy: can't allocate region from the heap");
	pthread_mutex_init(g->gp_mtx);
	while (++i < g->args.philo_num)
		pthread_mutex_init(g->forks + i, NULL);
	i = -1;
	while (++i < g->args.philo_num)
		g->philos[i].death_falg = 0;
}

void	starting_the_simulation(t_global *g)
{

}

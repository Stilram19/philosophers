/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:12:27 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/12 18:51:08 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

void	*sophia(void *arg)
{
	t_philos	*p;

	p = arg;
	while (1)
	{
		pthread_mutex_lock(&(p->lf));
		pthread_mutex_lock(&(p->rf));
		printf("%d is eating", p->id)
		pthread_mutex_unlock(&(p->rf));
		pthread_mutex_unlock(&(p->lf));
		printf("%d is sleeping")
	}
}

void	create_philosophers(t_global *g)
{
	t_sophia	i;

	i = -1;
	while (++i)
	{
		if (pthread_create(&(g->philos[i].t), NULL, sophia, &(g->philos[i])))
			exit_with_error("Logical fallacy: failed to create philosophers");
	}
}

void	simulation_init(t_global *g)
{
	t_sophia	i;

	i = -1;
	g->philos = malloc(sizeof(t_philos) * g->args.philo_num);
	if (!g->philos)
		exit_with_error("Logical fallacy: can't allocate region from the heap");
	while (++i < g->args.philo_num)
	{
		g->philos[i].id = i + 1;
		g->philos[i].state = THINKING;
		if (pthread_mutex_init(&(g->philos[i].lf), NULL))
			exit_with_error("Logical fallacy: Can't protect forks");
		if (!i)
			g->philos[g->args.philo_num - 1].rf = g->philos[i].lf;
		else
			g->philos[i - 1].rf = g->philos[i].lf;
	}
}

void	simulation_distr(t_global *g)
{
	t_sophia	i;

	i = -1;
	while (++i < g->args.philo_num)
		pthread_mutex_destroy(&(g->philos[i].lf));
	free(g->philos);
}

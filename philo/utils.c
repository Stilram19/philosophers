/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:03:23 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/14 18:08:45 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

time_t	_time(void)
{
	static time_t	start;
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (!start)
	{
		start = t.tv_sec * 1000000 + t.tv_usec;
		return (0);
	}
	return (t.tv_sec * 1000000 + t.tv_usec - start);
}

void	critical_section(t_philos *p)
{
	pthread_mutex_lock(&(p->critical_mtx));
	p->timer = _time();
	if (p->meals_count == p->args->number_of_meals)
	{
		p->done_eating = 1;
		return ;
	}
	p->meals_count++;
	pthread_mutex_unlock(&(p->critical_mtx));
}

void	supervising(t_philos *p)
{
	t_sophia		i;
	t_sophia		go_on;
	static t_sophia	total;
	go_on = EXIST;
	while (go_on)
	{
		i = -1;
		while (++i < p->args->philo_num)
		{
			pthread_mutex_lock(&(p->args->pass_mtx));
			pthread_mutex_lock(&(p[i].critical_mtx));
			if (_time() - p[i].timer >= (p->args->time_to_die) * 1000)
			{
				printf("%ld %d died\n", _time() / 1000, p[i].id);
				return ;
			}
			if (p[i].done_eating)
				((++total) && (p[i].done_eating = 0));
			if (total == p[i].args->philo_num)
				return ;
			p[i].args->pass_flag = VALID;
			pthread_mutex_unlock(&(p[i].critical_mtx));
			pthread_mutex_unlock(&(p->args->pass_mtx));
		}
	}
}

void	print_after_pass(t_philos *p, const char *state)
{
	t_sophia	wait;

	wait = VALID;
	while (wait)
	{
		pthread_mutex_lock(&(p->args->pass_mtx));
		if (p->args->pass_flag)
		{
			printf("%ld %d %s\n", _time() / 1000, p->id, state);
			p->args->pass_flag = EXPIRED;
			wait = INVALID;
		}
		pthread_mutex_unlock(&(p->args->pass_mtx));
	}
}

void	*sophia_routine(void *arg)
{
	t_philos	*p;

	p = arg;
	while (EXIST)
	{
		pthread_mutex_lock(p->lf);
		print_after_pass(p, " has taken a fork");
		pthread_mutex_lock(p->rf);
		critical_section(p);
		print_after_pass(p, " has taken a fork");
		print_after_pass(p, " is eating");
		usleep(p->args->time_to_eat * 1000);
		pthread_mutex_unlock(p->rf);
		pthread_mutex_unlock(p->lf);
		print_after_pass(p, " is sleeping");
		usleep(p->args->time_to_sleep * 1000);
		print_after_pass(p, " is thinking");
	}
	return (NULL);
}
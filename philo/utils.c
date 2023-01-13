/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:03:23 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/13 22:49:08 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

void	exit_with_error(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

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

void	supervising(t_philos *p)
{
	t_sophia	i;
	t_sophia	go_on;

	go_on = EXIST;
	while (go_on)
	{
		i = -1;
		while (++i < p->args->philo_num)
		{
			pthread_mutex_lock(&(p->args->pass_mtx));
			pthread_mutex_lock(&(p->args->time_mtx));
			if (_time() - p[i].timer >= (p->args->time_to_die) * 1000)
			{
				printf("%ld %d died\n", _time(), p[i].id);
				return ;
			}
			pthread_mutex_lock(&(p->args->time_mtx));
			p->args->pass_flag = VALID;
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
			printf("%ld %d %s\n", _time(), p->id, state);
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
		pthread_mutex_lock(&(p->lf));
		print_after_pass(p, " has taken a fork");
		pthread_mutex_lock(&(p->rf));
		p->timer = _time();
		print_after_pass(p, " has taken a fork");
		print_after_pass(p, " is eating");
		usleep(p->args->time_to_eat * 1000);
		pthread_mutex_unlock(&(p->rf));
		pthread_mutex_unlock(&(p->lf));
		print_after_pass(p, " is sleeping");
		usleep(p->args->time_to_sleep * 1000);
		print_after_pass(p, " is thinking");
	}
}
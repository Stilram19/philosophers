/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:03:23 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/01 18:12:32 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

t_time	_time(void)
{
	static t_time	start;
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
	pthread_mutex_unlock(&(p->critical_mtx));
	print_after_pass(p, "is eating");
	_usleep(p->args->time_to_eat * 1000);
	if (!(p->meals_count + 1))
		return ;
	p->meals_count++;
	if (p->meals_count == p->args->number_of_meals)
	{
		pthread_mutex_lock(&(p->args->meals_mtx));
		p->args->total_done_eating++;
		pthread_mutex_unlock(&(p->args->meals_mtx));
	}
}

t_sophia	supervising(t_philos *p)
{
	t_sophia		i;

	while (EXIST)
	{
		i = -1;
		while (++i < p->args->philo_num)
		{
			// pthread_mutex_lock(&(p->args->pass_mtx));
			pthread_mutex_lock(&(p[i].critical_mtx));
			if (_time() - p[i].timer >= (p->args->time_to_die) * 1000)
			{
				pthread_mutex_lock(p->write);
				printf("%ld %d died\n", _time() / 1000, p[i].id);
				return (SUCCESS);
			}
			pthread_mutex_unlock(&(p[i].critical_mtx));
			pthread_mutex_lock(&(p->args->meals_mtx));
			if (p->args->total_done_eating == p->args->philo_num)
				return (SUCCESS);
			pthread_mutex_unlock(&(p->args->meals_mtx));
			// pthread_mutex_unlock(&(p->args->pass_mtx));
			//_usleep(50);
			// _usleep(5000 / p->args->philo_num);
			usleep(50);
		}
		//usleep(50);
	}
	return (SUCCESS);
}

void	print_after_pass(t_philos *p, const char *state)
{
	pthread_mutex_lock(p->write);
	//_usleep(40);
	printf("%ld %d %s\n", _time() / 1000, p->id, state);
	pthread_mutex_unlock(p->write);
}

void	*sophia_routine(void *arg)
{
	t_philos	*p;

	p = arg;
	while (EXIST)
	{
		//if (p->meals_count == p->args->number_of_meals)
			//continue ;
		pthread_mutex_lock(p->lf);
		print_after_pass(p, "has taken his left fork");// remove
		pthread_mutex_lock(p->rf);
		print_after_pass(p, "has taken his right fork");// remove
		critical_section(p);
		pthread_mutex_unlock(p->rf);
		pthread_mutex_unlock(p->lf);
		print_after_pass(p, "is sleeping");
		_usleep(p->args->time_to_sleep * 1000);
		print_after_pass(p, "is thinking");
		_usleep(50);
	}
	return (NULL);
}

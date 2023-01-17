/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:03:23 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/17 17:02:10 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

void	_usleep(time_t t)
{
	int	i;

	i = 0;
	while (i < t)
	{
		usleep(10000);
		i += 10000;
	}
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

void	print_after_pass(t_philos *p, const char *state)
{
	pthread_mutex_lock(&(p->args->pass_mtx));
	printf("%ld %d %s\n", _time() / 1000, p->id, state);
	pthread_mutex_unlock(&(p->args->pass_mtx));
}

void	critical_section(t_philos *p)
{
	usleep(p->args->time_to_eat * 1000);
	pthread_mutex_lock(&(p->critical_mtx));
	p->timer = _time();
	print_after_pass(p, "is eating");
	pthread_mutex_unlock(&(p->critical_mtx));
	//usleep(p->args->time_to_eat * 1000);
	/*if (!(p->args->number_of_meals + 1))
		return ;
	pthread_mutex_lock(&(p->args->meals_mtx));
	p->meals_count++;
	if (p->meals_count == p->args->number_of_meals)
		p->args->total_done_eating++;
	pthread_mutex_unlock(&(p->args->meals_mtx));*/
}

t_sophia	supervising(t_philos *p)
{
	t_sophia	i;

	while (EXIST)
	{
		i = -1;
		while (++i < p->args->philo_num)
		{
			pthread_mutex_lock(&(p->args->pass_mtx));
			pthread_mutex_lock(&(p[i].critical_mtx));
			if (_time() - p[i].timer >= (p->args->time_to_die) * 1000)
			{
				printf("%ld %d died\n", _time() / 1000, p[i].id);
				return (SUCCESS);
			}
			pthread_mutex_unlock(&(p[i].critical_mtx));
		//	pthread_mutex_lock(&(p->args->meals_mtx));
			//if (p->args->total_done_eating == p->args->philo_num)
				//return (SUCCESS);
			//pthread_mutex_unlock(&(p->args->meals_mtx));
			pthread_mutex_unlock(&(p->args->pass_mtx));
		}
	}
	return (SUCCESS);
}

void	*sophia_routine(void *arg)
{
	t_philos	*p;

	p = arg;
	while (EXIST)
	{
		pthread_mutex_lock(p->lf);
		print_after_pass(p, "has taken his left fork");// remove 'his left'
		pthread_mutex_lock(p->rf);
		print_after_pass(p, "has taken his right fork");// remove 'his right'
		critical_section(p);
		pthread_mutex_unlock(p->rf);
		pthread_mutex_unlock(p->lf);
		print_after_pass(p, "is sleeping");
		usleep(p->args->time_to_sleep * 1000);
		print_after_pass(p, "is thinking");
	}
	return (NULL);
}

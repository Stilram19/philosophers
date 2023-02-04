/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:05:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 18:52:05 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

sem_t	*_sem_open(const char *path_name, int sem_value)
{
	sem_t	*sem;

	sem_unlink(path_name);
	sem = sem_open(path_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, sem_value);
	if (sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	return (sem);
}

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

void	print_after_pass(const char *str, sem_t *print_sem, int id)
{
	sem_wait(print_sem);
	printf("%ld %d %s\n", _time() / 1000, id, str);
	sem_post(print_sem);
}

void	*supervising(void *arg)
{
	t_args		*args;

	args = arg;
	while (EXIST)
	{
		sem_wait(args->data_race.sem);
		if (_time() - args->timer >= args->time_to_die * 1000)
			child_exit(args, DEATH_EXIT);
		if ((args->meals_num + 1) && args->eaten_meals >= args->meals_num)
			child_exit(args, DONE_EATING_EXIT);
		sem_post(args->data_race.sem);
		_usleep(50);
	}
	return (NULL);
}

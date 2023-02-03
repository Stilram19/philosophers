/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:24:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/03 18:50:21 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

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
	printf("%ld %d %s\n", _time(), id, str);
	sem_post(print_sem);
}

void	child_process_routine(t_args *args, int i)
{
	t_time	timer;

	timer = _timer();
	while (EXIST)
	{
		sem_wait(args->forks);
		print_after_pass("has taken a fork", args->print, i + 1);
		sem_wait(args->forks);
		print_after_pass("has taken a fork", args->print, i + 1);
		print_after_pass("is eating", args->print, i + 1);
		_usleep(args->time_to_eat * 1000);
		sem_post(args->forks);
		sem_post(args->forks);
		print_after_pass("is sleeping", args->print, i + 1);
		_usleep(args->time_to_sleep * 1000);
		print_after_pass("is thinking", args->print, i + 1);
	}
}

void	create_philosophers(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_num)
	{
		args->pids[i] = fork();
		if (!(args->pids[i]))
			child_process_routine(args, i);
		_usleep(50);
		i++;
	}
}

sem_t	_sem_open(const char *path_name, int sem_value)
{
	sem_t	*sem;

	sem = sem_open(path_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, sem_value);
	if (sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	return (sem);
}

void	start_simulation(t_args *args)
{
	t_sophia	i;
	t_sophia	b;

	i = -1;
	b = 0;
	args->forks = _sem_open("/forks", args->philo_num);
	args->print = _sem_open("/print", 1);
	args->timer_sem = malloc(sizeof(sem_t *) * args->philo_num);
	(args->timer_sem || (args->pids = malloc(sizeof(pid_t) * args->philo_num)));
	if (!(args->timer_sem && args->pids))
		exit(EXIT_FAILURE);
	while (++i < args->philo_num)
		args->timer_sem = _sem_open("/timer_sem", 1);
	create_philosophers(args);
}

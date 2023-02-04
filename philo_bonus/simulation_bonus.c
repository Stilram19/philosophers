/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:24:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 09:52:26 by obednaou         ###   ########.fr       */
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

void	supervisor(t_args *args)
{
	t_sophia	i;

	while (EXIST)
	{
		i = -1;
		while (++i < args->philo_num)
		{
			if (_time() - args->timer >= args->time_to_die)
				exit(EXIT_FAILURE);
		}
	}
}

void	child_process_routine(t_args *args, int i)
{
	pthread_t	supervisor;

	args->timer = _timer();
	if (pthread_create(&supervisor, NULL, supervisor, args)
		|| pthread_join(supervisor, NULL))
		exit(EXIT_FAILURE);
	while (EXIST)
	{
		sem_wait(args->forks);
		print_after_pass("has taken a fork", args->print, i + 1);
		sem_wait(args->forks);
		print_after_pass("has taken a fork", args->print, i + 1);
		print_after_pass("is eating", args->print, i + 1);
		if (_time() - args->timer >= args->time_to_die * 1000)
			exit(EXIT_FAILURE);
		args->timer = _time();
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
	t_sophia	i;

	i = -1;
	while (++i < args->philo_num)
	{
		args->pids[i] = fork();
		if (!(args->pids[i] + 1))
			exit(EXIT_FAILURE);
		if (!(args->pids[i]))
			child_process_routine(args, i);
		_usleep(50);
	}
}

void	wait_for_philosophers(t_args *args)
{
	t_sophia	i;
	t_sophia	status;

	i = -1;
	while (++i < args->philo_num)
	{
		waitpid(args->pids, &status, 0);
		if (status == EXIT_FAILURE)
			break ;
	}
	i = -1;
	sem_wait(args->print);
	while (++i < args->philo_num)
		kill(args->pids[i], SIGTERM);
}

sem_t	_sem_open(const char *path_name, int sem_value)
{
	sem_t	*sem;

	sem = sem_open(path_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, sem_value);
	if (sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	return (sem);
}

void	simulation_init(t_args *args)
{
	t_sophia	b;

	b = 0;
	args->forks = _sem_open("/forks", args->philo_num);
	args->print = _sem_open("/print", 1);
	args->pids = malloc(sizeof(pid_t) * args->philo_num);
	if (!(args->pids))
		exit(EXIT_FAILURE);
}

void	clean_up(t_args *args)
{
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_close(args->forks);
	sem_close(args->print);
}

void	start_simulation(t_args *args)
{
	if (!(args->philo_num))
		exit(EXIT_SUCCESS);
	simulation_init(args);
	create_philosophers(args);
	wait_for_philosophers(args);
	clean_up(args);
}

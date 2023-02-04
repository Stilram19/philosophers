/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:24:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 21:47:09 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

void	child_process_routine(t_args *args, int i)
{
	child_process_init(args, i);
	while (EXIST)
	{
		sem_wait(args->forks.sem);
		print_after_pass("has taken a fork", args->print.sem, i + 1);
		sem_wait(args->forks.sem);
		print_after_pass("has taken a fork", args->print.sem, i + 1);
		print_after_pass("is eating", args->print.sem, i + 1);
		sem_wait(args->data_race.sem);
		if (_time() - args->timer >= args->time_to_die * 1000)
			child_exit(args, DEATH_EXIT);
		args->timer = _time();
		sem_post(args->data_race.sem);
		_usleep(args->time_to_eat * 1000);
		sem_wait(args->data_race.sem);
		args->eaten_meals++;
		sem_post(args->data_race.sem);
		sem_post(args->forks.sem);
		sem_post(args->forks.sem);
		print_after_pass("is sleeping", args->print.sem, i + 1);
		_usleep(args->time_to_sleep * 1000);
		print_after_pass("is thinking", args->print.sem, i + 1);
		_usleep(50);
	}
}

void	create_philosophers(t_args *args)
{
	t_sophia		i;

	i = -1;
	_time();
	while (++i < args->philo_num)
	{
		args->pids[i] = fork();
		if (!(args->pids[i] + 1))
			exit(EXIT_FAILURE);
		if (!(args->pids[i]))
			child_process_routine(args, i);
		_usleep(100);
	}
}

void	wait_for_philosophers(t_args *args)
{
	t_sophia	i;
	t_sophia	dead_philos;
	t_sophia	status;

	i = -1;
	while (++i < args->philo_num)
	{
		waitpid(args->pids[i], &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE
			|| WEXITSTATUS(status) == DEATH_EXIT)
			break ;
	}
	dead_philos = i + 1;
	i = -1;
	sem_wait(args->print.sem);
	if (WEXITSTATUS(status) == DEATH_EXIT)
		printf("%ld %d died\n", _time() / 1000, dead_philos);
	while (++i < args->philo_num)
		kill(args->pids[i], SIGTERM);
}

void	simulation_init(t_args *args)
{
	t_sophia	i;

	i = -1;
	args->eaten_meals = 0;
	args->forks.name = "/forks";
	args->print.name = "/print";
	args->forks.sem = _sem_open(args->forks.name, args->philo_num);
	args->print.sem = _sem_open(args->print.name, 1);
	args->pids = malloc(sizeof(pid_t) * args->philo_num);
	if (!(args->pids))
		parent_exit(args, EXIT_FAILURE);
}

void	simulation(t_args *args)
{
	if (!(args->philo_num))
		exit(EXIT_SUCCESS);
	simulation_init(args);
	create_philosophers(args);
	wait_for_philosophers(args);
	parent_exit(args, EXIT_SUCCESS);
}

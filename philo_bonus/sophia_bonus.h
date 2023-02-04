/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophia_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:23:51 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 16:30:15 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHIA_BONUS_H
# define SOPHIA_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include "my_reference_bonus.h"

t_time		_time(void);
t_sophia	_usleep(t_time t);
t_sophia	ft_strlen(const char *str);
t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n);
t_sophia	detecting_fallacies(t_sophia argc, char **argv, t_args *args);
sem_t		*_sem_open(const char *path_name, int sem_value);
void		child_process_init(t_args *args, int i);
void		print_after_pass(const char *str, sem_t *print_sem, int id);
void		child_exit(t_args *args, t_sophia status);
void		parent_exit(t_args *args, t_sophia status);
void		child_process_routine(t_args *args, int i);
void		simulation(t_args *args);
void		*supervising(void *args);

#endif
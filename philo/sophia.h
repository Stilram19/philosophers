/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophia.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:42:36 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/13 21:06:30 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHIA_H
# define SOPHIA_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "my_reference.h"


void		exit_with_error(const char *str);
void		simulation_init(t_philos *p, t_args *args);
void		stop_simulation(t_philos *p);
void		detecting_fallacies(int argc, char **argv, t_args *args);
void		print_after_pass(t_philos *p, const char *state);
void		start_simulation(t_args *arg);
void		*sophia_routine(void *arg);
void		supervising(t_philos *p);
t_sophia	ft_strlen(const char *arg);
t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n);
time_t		_time(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophia.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:42:36 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/14 14:29:32 by obednaou         ###   ########.fr       */
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


void		stop_simulation(t_philos *p);
void		*sophia_routine(void *arg);
void		supervising(t_philos *p);
void		print_after_pass(t_philos *p, const char *state);
time_t		_time(void);
t_sophia	start_simulation(t_args *arg);
t_sophia	ft_strlen(const char *arg);
t_sophia	simulation_init(t_philos *p, t_args *args);
t_sophia	detecting_fallacies(int argc, char **argv, t_args *args);
t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n);

#endif

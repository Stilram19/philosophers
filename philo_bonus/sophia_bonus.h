/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophia_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:23:51 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/03 17:23:52 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHIA_BONUS_H
# define SOPHIA_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include "my_reference_bonus.h"

t_sophia	detecting_fallacies(t_sophia argc, char **argv, t_sophia *ptr_args);
t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n);
t_sophia	ft_strlen(const char *str);
void		start_simulation(t_args *args);

#endif
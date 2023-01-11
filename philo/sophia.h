/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophia.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:42:36 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 18:11:49 by obednaou         ###   ########.fr       */
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

t_sophia	ft_strlen(const char *arg);
t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n);
void		exit_with_error(const char *str);
void		detecting_fallacies(int argc, char **argv, t_args *args);

#endif
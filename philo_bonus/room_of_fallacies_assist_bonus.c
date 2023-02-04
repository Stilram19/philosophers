/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_of_fallacies_assist_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:41:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 16:16:48 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

t_sophia	ft_strlen(const char *str)
{
	t_sophia	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

t_sophia	ft_strncmp(const char *s1, const char *s2, t_sophia n)
{
	t_sophia	i;

	i = 0;
	while (n-- && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		i++;
	}
	return (0);
}

void	parent_exit(t_args *args, t_sophia status)
{
	sem_unlink(args->print.name);
	sem_unlink(args->forks.name);
	sem_close(args->forks.sem);
	sem_close(args->print.sem);
	exit(status);
}

void	child_exit(t_args *args, t_sophia status)
{
	sem_unlink(args->data_race.name);
	sem_close(args->data_race.sem);
	exit(status);
}

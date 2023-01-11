/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_of_fallacies_assist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:09:22 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 16:27:57 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

t_sophia	ft_strlen(const char *str)
{
	t_sophia	i;

	i = NIHIL;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:20:54 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/11 21:06:16 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

pthread_mutex_t	mtx;

void	*thread_body(void *arg)
{
	static int	test;

	pthread_mutex_lock(&mtx);
	printf("%d\n", test);
	test++;
	pthread_mutex_unlock(&mtx);
	return (NULL);
}

int	main(void)
{
	int			i;
	pthread_t	t[4];

	i = -1;
	pthread_mutex_init(&mtx, NULL);
	while (++i < 4)
	{
		if (pthread_create(t + i, NULL, thread_body, NULL))
			exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < 4)
	{
		if (pthread_detach(t[i]))
			exit(EXIT_FAILURE);
	}
	pthread_exit(0);
	return (0);
}

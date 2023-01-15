/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:37 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/15 10:47:07 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	mtx;


void	*routine(void *arg)
{
	printf("waiting id %d\n", *(int *)arg);
	pthread_mutex_lock(&mtx);
	printf("Hello id %d\n", *(int *)arg);
	pthread_mutex_unlock(&mtx);
	free(arg);
	return (arg);
}

int	main(void)
{
	int	i;
	int	*ptr;
	pthread_t	t[6];

	i = 0;
	pthread_mutex_init(&(mtx), NULL);
	while (i < 6)
	{
		ptr = malloc(sizeof(int));
		*ptr = i + 1;
		if (pthread_create(&t[i], NULL, routine, ptr))
			exit(1);
		//usleep(10);
		i++;
	}
	system("leaks a.out");
	return (0);
}
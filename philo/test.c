/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:37 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/16 20:43:36 by obednaou         ###   ########.fr       */
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
	int	i;

	i = 0;
	sleep(1);
	pthread_mutex_lock(&mtx);
	printf("Succeeded to lock the mutex!!!!!!\n");
	pthread_mutex_unlock(&mtx);
	return (arg);
}

void	function(void)
{
	pthread_mutex_lock(&mtx);
	printf("Hello from main thread!\n");
}

int	main(void)
{
	pthread_t	t;

	pthread_mutex_init(&mtx, NULL);
	if (pthread_create(&t, NULL, routine, NULL))
		return (1);
	function();
	sleep(4);
	return (0);
}

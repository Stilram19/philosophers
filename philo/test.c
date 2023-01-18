/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:37 by obednaou          #+#    #+#             */
/*   Updated: 2023/01/18 16:36:45 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	mtx;
pthread_mutex_t mtx1;

void	*routine(void *arg)
{
	pthread_mutex_lock(&mtx);
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	pthread_mutex_lock(&mtx1);
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	pthread_mutex_unlock(&mtx1);
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	printf("Hello brother how are you doing..");
	pthread_mutex_unlock(&mtx);
	return (arg);
}

time_t	_time(void)
{
	static time_t	start;
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (!start)
	{
		start = t.tv_sec * 1000000 + t.tv_usec;
		return (0);
	}
	return (t.tv_sec * 1000000 + t.tv_usec - start);
}

void	_usleep(time_t time_up)
{
	while (_time() < time_up)
		usleep((time_up - _time()) / 2);
}

int	main(void)
{
	pthread_t	t;

	_time();
	pthread_mutex_init(&mtx, NULL);
	pthread_mutex_init(&mtx, NULL);
	if (pthread_create(&t, NULL, routine, NULL))
		return (1);
	if (pthread_join(t, NULL))
		return (1);
	printf("%ld\n", _time());
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:41:49 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/05 21:26:13 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

static int	ft_digits_count(int n)
{
	int	count;

	count = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	i = ft_digits_count(n);
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (0);
	if (n < 0)
		*ret = 45;
	if (!n)
		*ret = 48;
	*(ret + i) = 0;
	while (n)
	{
		i--;
		if (n < 0)
			*(ret + i) = -(n % 10) + 48;
		else
			*(ret + i) = n % 10 + 48;
		n /= 10;
	}
	return (ret);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while (i < dstsize - 1 && *(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!(s1 && s2))
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = malloc((i + j + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, i + 1);
	ft_strlcpy(join + i, s2, j + 1);
	return (join);
}

void	child_process_init(t_args *args)
{
	pthread_t	supervisor;

	args->freeable = ft_itoa(args->id);
	args->data_race.name = ft_strjoin("/philo", args->freeable);
	if (!(args->data_race.name))
		exit(EXIT_FAILURE);
	args->data_race.sem = _sem_open(args->data_race.name, 1);
	sem_wait(args->data_race.sem);
	if (!(args->id % 2))
		_usleep(1000);
	args->timer = _time();
	sem_post(args->data_race.sem);
	if (pthread_create(&supervisor, NULL, supervising, args)
		|| pthread_detach(supervisor))
		child_exit(args, EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:17:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/03 16:41:36 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia_bonus.h"

// atomic operations used in semaphores
// void	wait
// {
//	while (S <= 0);
//	S--;
// }
// void	signal
// {
//	S++;
// }
//
// a thread is an execution (or execution flow) inside a process.
// a thread is the unit of execution within a process.

int	main(void)
{
	sem_t	*s;

	s = sem_open("/semaphorreeee", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);

	if (s == SEM_FAILED)
		return (1);
	sem_wait(s);
	printf("HELLO\n");
	sem_post(s);
	sem_unlink("/semaphorreeee");
	sem_close(s);
	return (0);
}

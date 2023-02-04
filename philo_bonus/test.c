/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:17:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/04 17:58:33 by obednaou         ###   ########.fr       */
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
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		exit(2);
	}
	waitpid(pid, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	return (0);
}

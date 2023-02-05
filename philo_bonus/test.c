/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:17:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/05 10:53:13 by obednaou         ###   ########.fr       */
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
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (!pid1)
	{
		//printf("Hello from child!\n");
		while (1);
	}
	pid2 = fork();
	if (!pid2)
	{
		exit(5);
	}
	//waitpid(0, &status, 0);
	//waitpid(pid2, &status, 0);
	waitpid(pid1, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
	return (0);
}

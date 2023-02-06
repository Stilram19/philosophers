/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:41:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/06 11:05:37 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

int	main(int argc, char **argv)
{
	t_args		*args;
	t_philos	*p;

	args = malloc(sizeof(t_args));
	if (!args || detecting_fallacies(argc, argv, args)
		|| simulation(args, &p))
		return (ERROR);
	return (SUCCESS);
}

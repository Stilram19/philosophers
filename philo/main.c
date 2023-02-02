/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:41:58 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/02 19:57:44 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophia.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args || detecting_fallacies(argc, argv, args)
		|| start_simulation(args))
		return (ERROR);
	return (SUCCESS);
}
